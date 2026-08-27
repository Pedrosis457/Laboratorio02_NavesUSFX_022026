// ============================================================================
//  LABORATORIO 02 - Programacion Avanzada (SIS457)
//  Universidad San Francisco Xavier de Chuquisaca
//
//  CLASE PADRE de toda la jerarquia de enemigos.
//
//      Enemigo
//        |-- EnemigoAereo      -> EAHelicoptero, EAAvion, EADron
//        |-- EnemigoTerrestre  -> ETSoldado, ETTanque, ETCamion, ETBlindado
//        |-- EnemigoAcuatico   -> EABarco, EALancha, EAMotoAcuatica
//
//  Cada enemigo pertenece a una cuadrilla y lleva su propio objeto
//  FTimerHandle, que es el que controla cuando desaparece del escenario.
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class NAVESUSFX_022026_API AEnemigo : public AActor
{
	GENERATED_BODY()

public:
	AEnemigo();

	virtual void Tick(float DeltaTime) override;

	/**
	 * Alta del enemigo en una cuadrilla.
	 * @param NumeroCuadrilla   1 o 2
	 * @param CentroCuadrilla   punto del escenario donde opera la cuadrilla
	 * @param Segundos          cuanto vive antes de desaparecer (0 = no desaparece)
	 */
	void ConfigurarCuadrilla(int32 NumeroCuadrilla, const FVector& CentroCuadrilla, float Segundos);

	int32 ObtenerCuadrilla() const { return Cuadrilla; }
	FString ObtenerTipo() const { return Tipo; }
	FVector ObtenerDestino() const { return Destino; }

protected:
	virtual void BeginPlay() override;

	/**
	 * Desplazamiento del enemigo. Es virtual: cada familia lo redefine para
	 * moverse a su manera (volando, por tierra o sobre el agua).
	 */
	virtual void Mover(float DeltaTime);

	/** Sortea un nuevo punto del escenario dentro de la zona de la cuadrilla. */
	virtual void ElegirNuevoDestino();

	/** Lo dispara el FTimerHandle: el enemigo se retira del escenario. */
	virtual void Desaparecer();

	/** Utilitario que usan las subclases dentro de su constructor. */
	void ConfigurarApariencia(const TCHAR* RutaMalla, const FVector& Escala, const FLinearColor& NuevoColor);

	// ---------------------------------------------------------------- Componentes

	/**
	 * La raiz es un componente vacio, NO la malla. Las subclases mueven la malla
	 * en local (cabeceo, balanceo, giro de rotor); si la malla fuera la raiz esos
	 * movimientos sobrescribirian la posicion del actor en el mundo.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Enemigo|Componentes")
	USceneComponent* Raiz;

	UPROPERTY(VisibleAnywhere, Category = "Enemigo|Componentes")
	UStaticMeshComponent* Malla;

	// ---------------------------------------------------------------- Identidad

	UPROPERTY(EditAnywhere, Category = "Enemigo")
	FString Tipo;

	UPROPERTY(VisibleAnywhere, Category = "Enemigo|Cuadrilla")
	int32 Cuadrilla;

	// ---------------------------------------------------------------- Movimiento

	UPROPERTY(EditAnywhere, Category = "Enemigo|Movimiento")
	float Velocidad;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Movimiento")
	float VelocidadDeGiro;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Movimiento")
	float DistanciaDeLlegada;

	UPROPERTY(VisibleAnywhere, Category = "Enemigo|Movimiento")
	FVector Destino;

	// ---------------------------------------------------------------- Zona

	UPROPERTY(EditAnywhere, Category = "Enemigo|Zona")
	FVector CentroDeZona;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Zona")
	float RadioDeZona;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Zona")
	float AlturaMinima;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Zona")
	float AlturaMaxima;

	// ---------------------------------------------------------------- Desaparicion

	/** OBJETO FTimerHandle que controla la desaparicion (exigido por el enunciado). */
	FTimerHandle TemporizadorDesaparicion;

	UPROPERTY(VisibleAnywhere, Category = "Enemigo|Cuadrilla")
	float SegundosDeVida;

	// ---------------------------------------------------------------- Auxiliares

	/**
	 * Rotacion con la que la subclase dejo la malla en su constructor (por ejemplo
	 * el cono del avion o de la lancha, inclinado para que el morro mire adelante).
	 * Las familias que rotan la malla en cada Tick deben componer sobre esta base,
	 * o borrarian esa inclinacion inicial.
	 */
	FRotator RotacionBaseDeMalla;

	float TiempoVivo;

	FLinearColor Color;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialDinamico;
};
