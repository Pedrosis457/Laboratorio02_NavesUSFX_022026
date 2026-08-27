# Guion del video — Laboratorio 02 (máximo 3 minutos)

**Cómo grabar:** `Win + G` → botón de grabar. El video queda en `Videos\Capturas`.
**Dónde subirlo:** YouTube en modo **"No listado"**. Ese link va al ecampus.

---

## 0:00 – 0:15 · Presentación

> "Buenas, soy [tu nombre]. Programación Avanzada, SIS457. Voy a explicar el
> Laboratorio 02: la jerarquía de clases de enemigos y las dos cuadrillas, hecho
> en Unreal Engine 4.27 con C++."

---

## 0:15 – 0:50 · La jerarquía de clases

**En pantalla:** Visual Studio, Explorador de soluciones con los archivos a la vista.

> "El laboratorio pedía una clase padre `Enemigo` y de ella tres clases hijas.
> Acá están: `EnemigoAereo`, `EnemigoTerrestre` y `EnemigoAcuatico`."

> "Y de cada una salen sus subclases: helicóptero, avión y dron; soldado, tanque,
> camión y blindado; barco, lancha y moto acuática. Son 14 clases en total."

Abrir `Enemigo.h` y señalar:
- el comentario de cabecera que dibuja el árbol completo
- `virtual void Mover(float DeltaTime)`
- `FTimerHandle TemporizadorDesaparicion`

---

## 0:50 – 1:20 · El polimorfismo

**En pantalla:** `EnemigoAereo.cpp` y `EnemigoTerrestre.cpp`.

> "`Mover` es virtual, y cada familia lo redefine. El aéreo llama al método del
> padre y le suma el vaivén del vuelo y el giro del rotor. El terrestre, en cambio,
> se pega al piso: fuerza la altura y agrega el traqueteo del chasis."

> "Y `ElegirNuevoDestino` también es virtual: el terrestre obliga a que el destino
> esté a ras del suelo, y el acuático lo corre hacia la zona de agua. Por eso cada
> familia se mueve distinto aunque compartan el mismo motor de desplazamiento."

---

## 1:20 – 1:50 · Las dos cuadrillas y el FTimerHandle

**En pantalla:** `NavesUSFX_022026GameModeBase.cpp`, función `DesplegarCuadrillaUno`.

> "Las dos cuadrillas tienen cada una su centro de operaciones: la primera en X
> menos 3000 y la segunda en X más 3000. Como cada enemigo sortea sus destinos
> alrededor del centro de su cuadrilla, las dos se mueven de forma independiente."

Señalar los tiempos 10, 14, 18, 22 y 26.

> "Cada miembro de la cuadrilla 1 recibe un tiempo de vida distinto. En el
> `BeginPlay` del enemigo ese tiempo arma un `FTimerHandle`, que es el objeto que
> controla su desaparición, como pedía el enunciado."

Ir a `VigilarCuadrillaUno`:

> "Y acá está la condición de la cuadrilla 2: un segundo temporizador cuenta cada
> medio segundo cuántos siguen vivos. Solo cuando llega a **cero** despliega la
> segunda cuadrilla."

---

## 1:50 – 2:45 · Demostración

**En pantalla:** Unreal, presionar **▶ Play**.

> "Al dar Play aparece la cuadrilla 1 a la izquierda, con sus cinco miembros de las
> tres familias: el helicóptero y el avión volando, el soldado y el tanque por
> tierra, y el barco sobre el agua."

Señalar el contador amarillo:

> "Arriba se ve el contador: cinco de cinco en escena."

Esperar y narrar mientras desaparecen:

> "A los diez segundos desaparece el primero, y así uno por uno. Vean cómo el
> contador va bajando."

Cuando llega a 0:

> "Y ahí, apenas desaparece el último, entra la cuadrilla 2 al otro lado del
> escenario: dron, camión, blindado, lancha y moto acuática."

---

## 2:45 – 3:00 · Cierre

> "El código está en el repositorio de GitHub, el link está en la entrega del
> ecampus. Gracias."

---

## Checklist antes de grabar

- [ ] Abrir Unreal y esperar a que cargue del todo
- [ ] Tener abiertos en Visual Studio: `Enemigo.h`, `EnemigoAereo.cpp`,
      `EnemigoTerrestre.cpp` y el GameMode
- [ ] Cerrar pestañas y ventanas ajenas al trabajo
- [ ] Probar el micrófono
- [ ] **Ojo con el tiempo:** la demo completa tarda 26 segundos hasta que entra la
      cuadrilla 2. Ensaya para que te entre en los 3 minutos.
