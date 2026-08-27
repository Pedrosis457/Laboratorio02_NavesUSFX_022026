// LABORATORIO 02 - Tanque: el mas lento y pesado, pero el mas grande.

#include "ETTanque.h"
#include "Components/StaticMeshComponent.h"

AETTanque::AETTanque()
{
	Tipo = TEXT("ETTanque");
	Velocidad = 220.0f;
	VelocidadDeGiro = 1.2f;
	AlturaDeRodaje = 85.0f;
	AmplitudDeTraqueteo = 2.5f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cube.Cube"),
		FVector(3.60f, 2.20f, 1.20f), FLinearColor(0.22f, 0.30f, 0.16f));
}
