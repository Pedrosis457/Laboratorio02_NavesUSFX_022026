// LABORATORIO 02 - Avion: el mas rapido y el que vuela mas alto.

#include "EAAvion.h"
#include "Components/StaticMeshComponent.h"

AEAAvion::AEAAvion()
{
	Tipo = TEXT("EAAvion");
	Velocidad = 900.0f;
	VelocidadDeGiro = 1.8f;
	AlturaMinima = 1200.0f;
	AlturaMaxima = 1900.0f;
	AmplitudVertical = 90.0f;
	FrecuenciaVertical = 0.9f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cone.Cone"),
		FVector(1.60f, 1.60f, 4.20f), FLinearColor(0.88f, 0.88f, 0.92f));

	// El cono apunta a +Z; se lo inclina para que el morro mire hacia adelante.
	Malla->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}
