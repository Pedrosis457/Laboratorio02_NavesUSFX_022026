// LABORATORIO 02 - Clase hija de Enemigo: familia TERRESTRE.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoTerrestre.generated.h"

/** Se desplaza pegado al suelo. Redefine el destino para que nunca despegue. */
UCLASS()
class NAVESUSFX_022026_API AEnemigoTerrestre : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigoTerrestre();

protected:
	virtual void Mover(float DeltaTime) override;
	virtual void ElegirNuevoDestino() override;

	/** Altura a la que circula, fija: es un vehiculo de tierra. */
	UPROPERTY(EditAnywhere, Category = "Enemigo|Terrestre")
	float AlturaDeRodaje;

	/** Balanceo lateral del chasis al avanzar. */
	UPROPERTY(EditAnywhere, Category = "Enemigo|Terrestre")
	float AmplitudDeTraqueteo;
};
