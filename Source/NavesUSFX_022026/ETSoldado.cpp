// LABORATORIO 02 - Soldado: infanteria, rapida y de giro agil.

#include "ETSoldado.h"
#include "Components/StaticMeshComponent.h"

AETSoldado::AETSoldado()
{
	Tipo = TEXT("ETSoldado");
	Velocidad = 330.0f;
	VelocidadDeGiro = 4.0f;
	AlturaDeRodaje = 110.0f;
	AmplitudDeTraqueteo = 7.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"),
		FVector(0.90f, 0.90f, 2.20f), FLinearColor(0.20f, 0.50f, 0.20f));
}
