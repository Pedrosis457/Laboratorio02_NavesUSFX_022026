// LABORATORIO 02 - Lancha: mas ligera y veloz que el barco.

#include "EALancha.h"
#include "Components/StaticMeshComponent.h"

AEALancha::AEALancha()
{
	Tipo = TEXT("EALancha");
	Velocidad = 430.0f;
	VelocidadDeGiro = 2.2f;
	AmplitudDeOleaje = 38.0f;
	AmplitudDeBalanceo = 14.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Cone.Cone"),
		FVector(1.30f, 1.30f, 2.80f), FLinearColor(0.95f, 0.55f, 0.05f));

	Malla->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
}
