# NavesUSFX_022026 — Laboratorio 02

**Materia:** Programación Avanzada (SIS457)
**Docente:** Ing. Carlos Walter Pacheco Lora
**Motor:** Unreal Engine 4.27 — C++

Desarrollado a partir del código fuente del Laboratorio 01.

---

## 1. Qué pedía el laboratorio

> Crear una clase padre `Enemigo`, y de ella derivar 3 clases hijas.
> De esas tres, crear las subclases indicadas.
> Con todas estas clases, armar dos cuadrillas que se muestren y muevan
> independientemente en el escenario, donde la segunda cuadrilla aparece
> solamente cuando todos los miembros de la primera desaparezcan.
> La desaparición debe ser controlada por un objeto `FTimerHandle`.

> **Nota sobre el enunciado:** la lista de clases hijas dice
> *"EnemigoAereo, EnemigoTerrestre y Enemigo Aereo"*, repitiendo la primera.
> Por las subclases que se piden después (Barco, Lancha, Moto Acuática), la
> tercera familia corresponde a **`EnemigoAcuatico`**, y así fue implementada.

## 2. La jerarquía — 14 clases

```
AEnemigo                          clase padre
│
├── AEnemigoAereo                 clase hija
│   ├── AEAHelicoptero
│   ├── AEAAvion
│   └── AEADron
│
├── AEnemigoTerrestre             clase hija
│   ├── AETSoldado
│   ├── AETTanque
│   ├── AETCamion
│   └── AETBlindado
│
└── AEnemigoAcuatico              clase hija
    ├── AEABarco
    ├── AEALancha
    └── AEAMotoAcuatica
```

## 3. El polimorfismo

`AEnemigo` define dos métodos `virtual` que cada familia redefine:

| Método | Qué hace en el padre | Cómo lo cambia cada familia |
|---|---|---|
| `ElegirNuevoDestino()` | Sortea un punto dentro del área de la cuadrilla | El **terrestre** fuerza `Z` a ras del suelo; el **acuático** corre el destino a la zona de agua |
| `Mover()` | Avanza hacia el destino girando con `RInterpTo` | El **aéreo** suma vaivén vertical y giro de rotor; el **terrestre** se pega al piso y traquetea; el **acuático** flota con oleaje y balanceo |

Así, las tres familias comparten el mismo motor de desplazamiento heredado del
padre, pero cada una se mueve de forma reconociblemente distinta.

Las 10 subclases finales solo definen su constructor: ahí ajustan su malla,
escala, color, velocidad y altura. Por eso todas se distinguen a simple vista.

| Clase | Forma | Rasgo |
|---|---|---|
| `EAHelicoptero` | Cilindro amarillo | Vuelo bajo, rotor girando |
| `EAAvion` | Cono blanco | El más rápido y el más alto |
| `EADron` | Esfera verde | Pequeño, ágil, vuelo nervioso |
| `ETSoldado` | Cilindro verde | Infantería, giro ágil |
| `ETTanque` | Caja verde oscuro | El más lento y grande |
| `ETCamion` | Caja marrón alargada | Transporte, velocidad media |
| `ETBlindado` | Caja gris | Más ágil que el tanque |
| `EABarco` | Caja roja alargada | Navegación lenta y estable |
| `EALancha` | Cono naranja | Más ligera y veloz |
| `EAMotoAcuatica` | Esfera rosa achatada | La más rápida, salta con el oleaje |

## 4. Las dos cuadrillas

| | Cuadrilla 1 | Cuadrilla 2 |
|---|---|---|
| Centro de operaciones | `X = -3000` | `X = +3000` |
| Miembros | EAHelicoptero, EAAvion, ETSoldado, ETTanque, EABarco | EADron, ETCamion, ETBlindado, EALancha, EAMotoAcuatica |
| Tiempo de vida | 10, 14, 18, 22 y 26 s | Permanente |

**Se mueven independientemente** porque cada cuadrilla opera en su propia mitad
del escenario: al configurar un enemigo se le pasa el centro de su cuadrilla, y
todos sus destinos se sortean alrededor de ese centro. Ninguna interfiere con la
otra. Cada cuadrilla tiene además su propia zona de agua para su familia acuática.

## 5. La desaparición controlada por FTimerHandle

Cada `AEnemigo` tiene su **propio objeto `FTimerHandle`**:

```cpp
/** OBJETO FTimerHandle que controla la desaparicion. */
FTimerHandle TemporizadorDesaparicion;
```

En su `BeginPlay()` se programa:

```cpp
if (SegundosDeVida > 0.0f)
{
    GetWorldTimerManager().SetTimer(TemporizadorDesaparicion, this,
        &AEnemigo::Desaparecer, SegundosDeVida, false);
}
```

Como los tiempos están escalonados (10, 14, 18, 22, 26 s), los miembros de la
cuadrilla 1 **van desapareciendo uno por uno**, no todos de golpe.

## 6. Cómo entra la cuadrilla 2

El GameMode usa un **segundo `FTimerHandle`** (`TemporizadorVigilancia`) que se
ejecuta cada medio segundo y cuenta cuántos miembros de la cuadrilla 1 siguen
vivos:

```cpp
if (Vivos == 0 && !bCuadrillaDosDesplegada)
{
    bCuadrillaDosDesplegada = true;
    GetWorldTimerManager().ClearTimer(TemporizadorVigilancia);
    DesplegarCuadrillaDos();
}
```

La condición es estricta: **cero miembros vivos**. Mientras quede aunque sea uno,
la segunda cuadrilla no aparece. El contador se ve en pantalla en todo momento
(`Cuadrilla 1: N de 5 en escena`).

## 7. Dos detalles de implementación que vale la pena señalar

**La raíz del actor es un `USceneComponent`, no la malla.** Las subclases mueven
la malla en coordenadas locales (cabeceo, balanceo, giro del rotor). Si la malla
fuera el `RootComponent`, ese movimiento local sobrescribiría la posición del
actor en el mundo y los enemigos quedarían clavados en el origen oscilando, sin
desplazarse nunca.

**Se usa `SpawnActorDeferred` en lugar de `SpawnActor`.** Hay que asignarle al
enemigo su cuadrilla y su tiempo de vida **antes** de que corra su `BeginPlay`,
porque es ahí donde arma su `FTimerHandle`. Con un spawn normal el `BeginPlay` se
ejecuta de inmediato y la configuración llegaría tarde: el temporizador nunca se
programaría.

## 8. Cómo ejecutarlo

1. Abrir `NavesUSFX_022026.uproject` con Unreal Engine 4.27
2. Presionar **Play**

Controles: **W A S D** desplazarse · **Mouse** mirar · **E/Espacio** subir ·
**Q/Ctrl** bajar · **Esc** salir.

El escenario, las zonas de agua y la posición inicial del jugador se generan por
código, así que no hay que configurar nada en el editor.

### Qué se ve

- **0 s** — Aparece la cuadrilla 1 a la izquierda: 5 enemigos de las tres familias
- **10 a 26 s** — Van desapareciendo uno por uno, con aviso naranja en pantalla
- **Al llegar a 0** — Aparece la cuadrilla 2 a la derecha con sus 5 miembros

## 9. Estructura del código

```
Source/NavesUSFX_022026/
├── Enemigo.h / .cpp                        CLASE PADRE
├── EnemigoAereo.h / .cpp                   clase hija
├── EnemigoTerrestre.h / .cpp               clase hija
├── EnemigoAcuatico.h / .cpp                clase hija
├── EAHelicoptero, EAAvion, EADron          subclases aéreas
├── ETSoldado, ETTanque, ETCamion, ETBlindado   subclases terrestres
├── EABarco, EALancha, EAMotoAcuatica       subclases acuáticas
└── NavesUSFX_022026GameModeBase.h / .cpp   las dos cuadrillas
```

## 10. Video explicativo

*(pendiente de agregar el enlace)*
