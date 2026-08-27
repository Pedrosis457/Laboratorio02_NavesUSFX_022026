// LABORATORIO 02 - Moto acuatica: la mas rapida y la que mas salta con el oleaje.

#include "EAMotoAcuatica.h"
#include "Components/StaticMeshComponent.h"

AEAMotoAcuatica::AEAMotoAcuatica()
{
	Tipo = TEXT("EAMotoAcuatica");
	Velocidad = 560.0f;
	VelocidadDeGiro = 3.2f;
	DistanciaDeLlegada = 150.0f;
	AmplitudDeOleaje = 55.0f;
	FrecuenciaDeOleaje = 3.2f;
	AmplitudDeBalanceo = 20.0f;

	ConfigurarApariencia(TEXT("/Engine/BasicShapes/Sphere.Sphere"),
		FVector(1.90f, 1.10f, 1.00f), FLinearColor(0.95f, 0.20f, 0.60f));
}
