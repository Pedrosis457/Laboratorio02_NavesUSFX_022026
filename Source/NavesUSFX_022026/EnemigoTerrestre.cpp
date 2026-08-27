// LABORATORIO 02 - Familia TERRESTRE.

#include "EnemigoTerrestre.h"
#include "Components/StaticMeshComponent.h"

AEnemigoTerrestre::AEnemigoTerrestre()
{
	Tipo = TEXT("EnemigoTerrestre");

	Velocidad = 380.0f;
	VelocidadDeGiro = 2.0f;
	Color = FLinearColor(0.35f, 0.28f, 0.12f);

	AlturaDeRodaje = 90.0f;
	AmplitudDeTraqueteo = 4.0f;
}

void AEnemigoTerrestre::ElegirNuevoDestino()
{
	Super::ElegirNuevoDestino();

	// Un vehiculo terrestre no vuela: el destino siempre queda a ras del suelo.
	Destino.Z = AlturaDeRodaje;
}

void AEnemigoTerrestre::Mover(float DeltaTime)
{
	Super::Mover(DeltaTime);

	// Se mantiene pegado al piso aunque el giro lo incline.
	FVector Posicion = GetActorLocation();
	Posicion.Z = AlturaDeRodaje;
	SetActorLocation(Posicion);

	FRotator Rotacion = GetActorRotation();
	Rotacion.Pitch = 0.0f;
	SetActorRotation(Rotacion);

	// Traqueteo del chasis.
	if (Malla)
	{
		Malla->SetRelativeRotation(RotacionBaseDeMalla + FRotator(0.0f, 0.0f,
			FMath::Sin(TiempoVivo * 9.0f) * AmplitudDeTraqueteo));
	}
}
