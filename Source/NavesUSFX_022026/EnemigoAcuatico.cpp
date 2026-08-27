// LABORATORIO 02 - Familia ACUATICA.

#include "EnemigoAcuatico.h"
#include "Components/StaticMeshComponent.h"

AEnemigoAcuatico::AEnemigoAcuatico()
{
	Tipo = TEXT("EnemigoAcuatico");

	Velocidad = 300.0f;
	VelocidadDeGiro = 1.5f;
	RadioDeZona = 1300.0f;
	Color = FLinearColor(0.10f, 0.35f, 0.55f);

	NivelDelAgua = 60.0f;
	AmplitudDeOleaje = 30.0f;
	FrecuenciaDeOleaje = 2.0f;
	AmplitudDeBalanceo = 10.0f;
}

void AEnemigoAcuatico::ElegirNuevoDestino()
{
	Super::ElegirNuevoDestino();

	// El destino se corre a la zona de agua y queda a nivel de la superficie.
	Destino += DesfaseDelAgua();
	Destino.Z = NivelDelAgua;
}

void AEnemigoAcuatico::Mover(float DeltaTime)
{
	Super::Mover(DeltaTime);

	FVector Posicion = GetActorLocation();
	Posicion.Z = NivelDelAgua;
	SetActorLocation(Posicion);

	FRotator Rotacion = GetActorRotation();
	Rotacion.Pitch = 0.0f;
	SetActorRotation(Rotacion);

	// Oleaje: la embarcacion sube, baja y se balancea sobre el agua.
	if (Malla)
	{
		Malla->SetRelativeLocation(FVector(0.0f, 0.0f,
			FMath::Sin(TiempoVivo * FrecuenciaDeOleaje) * AmplitudDeOleaje));

		// Se compone sobre la rotacion base para no borrar la inclinacion
		// que la subclase le dio a la malla en su constructor.
		Malla->SetRelativeRotation(RotacionBaseDeMalla + FRotator(0.0f, 0.0f,
			FMath::Sin(TiempoVivo * FrecuenciaDeOleaje * 0.7f) * AmplitudDeBalanceo));
	}
}
