// LABORATORIO 02 - Clase hija de Enemigo: familia AEREA.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoAereo.generated.h"

/** Vuela en altura. Redefine Mover() agregando oscilacion vertical y giro de malla. */
UCLASS()
class NAVESUSFX_022026_API AEnemigoAereo : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigoAereo();

protected:
	virtual void Mover(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Aereo")
	float AmplitudVertical;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Aereo")
	float FrecuenciaVertical;

	/** Grados por segundo que gira la malla sobre si misma (rotor, helices). */
	UPROPERTY(EditAnywhere, Category = "Enemigo|Aereo")
	float GiroDeMalla;
};
