// LABORATORIO 02 - Barco: casco largo, navegacion lenta y estable.

#include "EABarco.h"
#include "Components/StaticMeshComponent.h"

AEABarco::AEABarco()
{
	Tipo = TEXT("EABarco");
	Velocidad = 240.0f;
	VelocidadDeGiro = 1.0f;
	AmplitudDeOleaje = 24.0f;
	AmplitudDeBalanceo = 7.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cube.Cube"),
		FVector(4.40f, 1.60f, 1.10f), FLinearColor(0.60f, 0.12f, 0.12f));
}
