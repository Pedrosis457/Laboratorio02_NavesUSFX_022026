// LABORATORIO 02 - Camion: vehiculo largo de transporte, velocidad media.

#include "ETCamion.h"
#include "Components/StaticMeshComponent.h"

AETCamion::AETCamion()
{
	Tipo = TEXT("ETCamion");
	Velocidad = 300.0f;
	VelocidadDeGiro = 1.6f;
	AlturaDeRodaje = 100.0f;
	AmplitudDeTraqueteo = 5.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cube.Cube"),
		FVector(4.00f, 1.70f, 1.60f), FLinearColor(0.48f, 0.33f, 0.12f));
}
