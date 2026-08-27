// LABORATORIO 02 - Familia AEREA.

#include "EnemigoAereo.h"
#include "Components/StaticMeshComponent.h"

AEnemigoAereo::AEnemigoAereo()
{
	Tipo = TEXT("EnemigoAereo");

	Velocidad = 620.0f;
	AlturaMinima = 700.0f;
	AlturaMaxima = 1600.0f;
	Color = FLinearColor(0.20f, 0.60f, 1.00f);

	AmplitudVertical = 70.0f;
	FrecuenciaVertical = 1.5f;
	GiroDeMalla = 0.0f;
}

void AEnemigoAereo::Mover(float DeltaTime)
{
	// Recorrido heredado del padre...
	Super::Mover(DeltaTime);

	// ...mas el vaiven propio del vuelo.
	if (Malla)
	{
		const float Vaiven = FMath::Sin(TiempoVivo * FrecuenciaVertical) * AmplitudVertical;
		Malla->SetRelativeLocation(FVector(0.0f, 0.0f, Vaiven));

		if (!FMath::IsNearlyZero(GiroDeMalla))
		{
			Malla->AddLocalRotation(FRotator(0.0f, GiroDeMalla * DeltaTime, 0.0f));
		}
	}
}
