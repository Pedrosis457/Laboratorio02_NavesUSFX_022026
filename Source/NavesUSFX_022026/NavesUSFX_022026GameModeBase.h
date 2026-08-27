// ============================================================================
//  LABORATORIO 02 - Programacion Avanzada (SIS457)
//
//  El GameMode arma las DOS CUADRILLAS.
//  La cuadrilla 2 solo aparece cuando todos los miembros de la cuadrilla 1
//  han desaparecido (cada uno por su propio FTimerHandle).
// ============================================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavesUSFX_022026GameModeBase.generated.h"

class AEnemigo;

UCLASS()
class NAVESUSFX_022026_API ANavesUSFX_022026GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANavesUSFX_022026GameModeBase();

	virtual void BeginPlay() override;

protected:
	void DesplegarCuadrillaUno();
	void DesplegarCuadrillaDos();

	/** Corre cada medio segundo: cuando la cuadrilla 1 se vacia, entra la 2. */
	void VigilarCuadrillaUno();

	AEnemigo* CrearEnemigo(TSubclassOf<AEnemigo> ClaseEnemigo, int32 NumeroCuadrilla,
		const FVector& Centro, float SegundosDeVida);

	/**
	 * Sortea cuantos segundos vive un enemigo antes de desaparecer.
	 * Al ser aleatorio, el orden en que se retiran los miembros de la
	 * cuadrilla 1 cambia en cada partida.
	 */
	float SortearTiempoDeVida() const;

	void PrepararEscenario();
	void CrearPlano(const FVector& Posicion, const FVector& Escala, const FLinearColor& Color, bool bSolido);
	void ColocarJugador();
	void MostrarControles();

	// ---------------------------------------------------------------- Cuadrillas

	UPROPERTY()
	TArray<AEnemigo*> CuadrillaUno;

	UPROPERTY()
	TArray<AEnemigo*> CuadrillaDos;

	UPROPERTY(EditAnywhere, Category = "Cuadrillas")
	FVector CentroCuadrillaUno;

	UPROPERTY(EditAnywhere, Category = "Cuadrillas")
	FVector CentroCuadrillaDos;

	/** Extremos del rango del que se sortea el tiempo de vida, en segundos. */
	UPROPERTY(EditAnywhere, Category = "Cuadrillas")
	float VidaMinima;

	UPROPERTY(EditAnywhere, Category = "Cuadrillas")
	float VidaMaxima;

	FTimerHandle TemporizadorVigilancia;
	FTimerHandle TemporizadorJugador;

	bool bCuadrillaDosDesplegada;
};
