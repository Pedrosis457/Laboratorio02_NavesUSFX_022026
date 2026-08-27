// LABORATORIO 02 - Helicoptero: vuelo bajo y lento, con el rotor girando.

#include "EAHelicoptero.h"
#include "Components/StaticMeshComponent.h"

AEAHelicoptero::AEAHelicoptero()
{
	Tipo = TEXT("EAHelicoptero");
	Velocidad = 480.0f;
	AlturaMinima = 600.0f;
	AlturaMaxima = 1000.0f;
	AmplitudVertical = 55.0f;
	GiroDeMalla = 600.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"),
		FVector(2.60f, 2.60f, 1.20f), FLinearColor(0.95f, 0.75f, 0.10f));
}
