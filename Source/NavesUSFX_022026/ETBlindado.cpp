// LABORATORIO 02 - Blindado: mas agil que el tanque y bien protegido.

#include "ETBlindado.h"
#include "Components/StaticMeshComponent.h"

AETBlindado::AETBlindado()
{
	Tipo = TEXT("ETBlindado");
	Velocidad = 360.0f;
	VelocidadDeGiro = 2.4f;
	AlturaDeRodaje = 95.0f;
	AmplitudDeTraqueteo = 4.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cube.Cube"),
		FVector(2.80f, 1.90f, 1.30f), FLinearColor(0.32f, 0.32f, 0.38f));
}
