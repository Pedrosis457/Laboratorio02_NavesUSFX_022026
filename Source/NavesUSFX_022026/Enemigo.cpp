// ============================================================================
//  LABORATORIO 02 - Implementacion de la clase padre Enemigo.
// ============================================================================

#include "Enemigo.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;

	// --- Raiz vacia ----------------------------------------------------------
	Raiz = CreateDefaultSubobject<USceneComponent>(TEXT("Raiz"));
	RootComponent = Raiz;

	// --- Cuerpo visible ------------------------------------------------------
	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	Malla->SetupAttachment(Raiz);
	Malla->SetMobility(EComponentMobility::Movable);
	Malla->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaPorDefecto(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (MallaPorDefecto.Succeeded())
	{
		Malla->SetStaticMesh(MallaPorDefecto.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBasico(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (MaterialBasico.Succeeded())
	{
		Malla->SetMaterial(0, MaterialBasico.Object);
	}

	Malla->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));

	// --- Valores por defecto -------------------------------------------------
	Tipo = TEXT("Enemigo");
	Cuadrilla = 0;

	Velocidad = 500.0f;
	VelocidadDeGiro = 3.0f;
	DistanciaDeLlegada = 180.0f;
	Destino = FVector::ZeroVector;

	CentroDeZona = FVector::ZeroVector;
	RadioDeZona = 1800.0f;
	AlturaMinima = 200.0f;
	AlturaMaxima = 900.0f;

	SegundosDeVida = 0.0f;
	TiempoVivo = 0.0f;
	Color = FLinearColor(0.7f, 0.7f, 0.7f);
	MaterialDinamico = nullptr;
}

void AEnemigo::ConfigurarApariencia(const TCHAR* RutaMalla, const FVector& Escala, const FLinearColor& NuevoColor)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> Buscador(RutaMalla);
	if (Buscador.Succeeded())
	{
		Malla->SetStaticMesh(Buscador.Object);
	}

	Malla->SetRelativeScale3D(Escala);
	Color = NuevoColor;
}

void AEnemigo::ConfigurarCuadrilla(int32 NumeroCuadrilla, const FVector& CentroCuadrilla, float Segundos)
{
	Cuadrilla = NumeroCuadrilla;
	CentroDeZona = CentroCuadrilla;
	SegundosDeVida = Segundos;
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();

	if (Malla)
	{
		// Se guarda la inclinacion que dejo el constructor de la subclase.
		RotacionBaseDeMalla = Malla->GetRelativeRotation();

		MaterialDinamico = Malla->CreateAndSetMaterialInstanceDynamic(0);
		if (MaterialDinamico)
		{
			MaterialDinamico->SetVectorParameterValue(TEXT("Color"), Color);
		}
	}

	ElegirNuevoDestino();

	// ================================================================
	//  El objeto FTimerHandle controla la desaparicion del enemigo.
	// ================================================================
	if (SegundosDeVida > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TemporizadorDesaparicion, this,
			&AEnemigo::Desaparecer, SegundosDeVida, false);
	}

	UE_LOG(LogTemp, Warning, TEXT("[Cuadrilla %d] %s en escena, desaparece en %.0f s"),
		Cuadrilla, *Tipo, SegundosDeVida);
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TiempoVivo += DeltaTime;
	Mover(DeltaTime);
}

void AEnemigo::ElegirNuevoDestino()
{
	// Un punto cualquiera del area de la cuadrilla.
	const float Angulo = FMath::FRandRange(0.0f, 2.0f * PI);
	const float Radio = FMath::FRandRange(RadioDeZona * 0.25f, RadioDeZona);

	Destino = CentroDeZona + FVector(
		FMath::Cos(Angulo) * Radio,
		FMath::Sin(Angulo) * Radio,
		0.0f);

	Destino.Z = FMath::FRandRange(AlturaMinima, AlturaMaxima);
}

void AEnemigo::Mover(float DeltaTime)
{
	const FVector Posicion = GetActorLocation();
	FVector Direccion = Destino - Posicion;
	const float Distancia = Direccion.Size();

	if (Distancia <= DistanciaDeLlegada)
	{
		ElegirNuevoDestino();
		return;
	}

	Direccion /= Distancia;

	SetActorLocation(Posicion + Direccion * Velocidad * DeltaTime);
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), Direccion.Rotation(), DeltaTime, VelocidadDeGiro));
}

void AEnemigo::Desaparecer()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Orange,
			FString::Printf(TEXT("Cuadrilla %d  ->  %s desaparece"), Cuadrilla, *Tipo));
	}

	UE_LOG(LogTemp, Warning, TEXT("[Cuadrilla %d] %s DESAPARECE (FTimerHandle a los %.0f s)"),
		Cuadrilla, *Tipo, SegundosDeVida);

	GetWorldTimerManager().ClearTimer(TemporizadorDesaparicion);
	Destroy();
}
