// LABORATORIO 02 - Clase hija de Enemigo: familia ACUATICA.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoAcuatico.generated.h"

/** Navega sobre la zona de agua, con oleaje y balanceo. */
UCLASS()
class NAVESUSFX_022026_API AEnemigoAcuatico : public AEnemigo
{
	GENERATED_BODY()

public:
	AEnemigoAcuatico();

	/** Desplazamiento de la zona de agua respecto al centro de la cuadrilla. */
	static FVector DesfaseDelAgua() { return FVector(0.0f, 2600.0f, 0.0f); }

protected:
	virtual void Mover(float DeltaTime) override;
	virtual void ElegirNuevoDestino() override;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Acuatico")
	float NivelDelAgua;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Acuatico")
	float AmplitudDeOleaje;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Acuatico")
	float FrecuenciaDeOleaje;

	UPROPERTY(EditAnywhere, Category = "Enemigo|Acuatico")
	float AmplitudDeBalanceo;
};
