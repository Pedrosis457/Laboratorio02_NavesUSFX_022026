// LABORATORIO 02 - Dron: pequeno, agil y de vuelo nervioso.

#include "EADron.h"
#include "Components/StaticMeshComponent.h"

AEADron::AEADron()
{
	Tipo = TEXT("EADron");
	Velocidad = 750.0f;
	VelocidadDeGiro = 5.0f;
	AlturaMinima = 450.0f;
	AlturaMaxima = 800.0f;
	AmplitudVertical = 45.0f;
	FrecuenciaVertical = 3.0f;
	GiroDeMalla = 900.0f;
	DistanciaDeLlegada = 140.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Sphere.Sphere"),
		FVector(1.40f, 1.40f, 1.40f), FLinearColor(0.15f, 0.90f, 0.55f));
}
