// ============================================================================
//  LABORATORIO 02 - Implementacion del GameMode: las dos cuadrillas.
// ============================================================================

#include "NavesUSFX_022026GameModeBase.h"

#include "Enemigo.h"
#include "EnemigoAcuatico.h"

#include "EAHelicoptero.h"
#include "EAAvion.h"
#include "EADron.h"
#include "ETSoldado.h"
#include "ETTanque.h"
#include "ETCamion.h"
#include "ETBlindado.h"
#include "EABarco.h"
#include "EALancha.h"
#include "EAMotoAcuatica.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

ANavesUSFX_022026GameModeBase::ANavesUSFX_022026GameModeBase()
{
	// Cada cuadrilla opera en su propia mitad del escenario: por eso se ven
	// y se mueven de forma independiente una de la otra.
	CentroCuadrillaUno = FVector(-3000.0f, 0.0f, 0.0f);
	CentroCuadrillaDos = FVector(3000.0f, 0.0f, 0.0f);

	bCuadrillaDosDesplegada = false;
}

void ANavesUSFX_022026GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PrepararEscenario();

	GetWorldTimerManager().SetTimer(TemporizadorJugador, this,
		&ANavesUSFX_022026GameModeBase::ColocarJugador, 0.2f, false);

	// Los enemigos se colocan en la escena por codigo C++ desde el BeginPlay.
	DesplegarCuadrillaUno();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Cyan,
			FString::Printf(TEXT("CUADRILLA 1 desplegada: %d miembros"), CuadrillaUno.Num()));
	}

	// Vigilancia: mientras queden miembros de la cuadrilla 1, la 2 no entra.
	GetWorldTimerManager().SetTimer(TemporizadorVigilancia, this,
		&ANavesUSFX_022026GameModeBase::VigilarCuadrillaUno, 0.5f, true);
}

// ---------------------------------------------------------------------------
//  Cuadrillas
// ---------------------------------------------------------------------------

void ANavesUSFX_022026GameModeBase::DesplegarCuadrillaUno()
{
	CuadrillaUno.Empty();

	// Tiempos de vida escalonados: van desapareciendo uno por uno,
	// cada uno por su propio FTimerHandle.
	CuadrillaUno.Add(CrearEnemigo(AEAHelicoptero::StaticClass(), 1, CentroCuadrillaUno, 10.0f));
	CuadrillaUno.Add(CrearEnemigo(AEAAvion::StaticClass(),       1, CentroCuadrillaUno, 14.0f));
	CuadrillaUno.Add(CrearEnemigo(AETSoldado::StaticClass(),     1, CentroCuadrillaUno, 18.0f));
	CuadrillaUno.Add(CrearEnemigo(AETTanque::StaticClass(),      1, CentroCuadrillaUno, 22.0f));
	CuadrillaUno.Add(CrearEnemigo(AEABarco::StaticClass(),       1, CentroCuadrillaUno, 26.0f));

	CuadrillaUno.RemoveAll([](AEnemigo* Enemigo) { return Enemigo == nullptr; });

	UE_LOG(LogTemp, Warning, TEXT("[GameMode] CUADRILLA 1 desplegada con %d miembros"), CuadrillaUno.Num());
}

void ANavesUSFX_022026GameModeBase::DesplegarCuadrillaDos()
{
	CuadrillaDos.Empty();

	// La segunda cuadrilla se queda en escena (SegundosDeVida = 0).
	CuadrillaDos.Add(CrearEnemigo(AEADron::StaticClass(),         2, CentroCuadrillaDos, 0.0f));
	CuadrillaDos.Add(CrearEnemigo(AETCamion::StaticClass(),       2, CentroCuadrillaDos, 0.0f));
	CuadrillaDos.Add(CrearEnemigo(AETBlindado::StaticClass(),     2, CentroCuadrillaDos, 0.0f));
	CuadrillaDos.Add(CrearEnemigo(AEALancha::StaticClass(),       2, CentroCuadrillaDos, 0.0f));
	CuadrillaDos.Add(CrearEnemigo(AEAMotoAcuatica::StaticClass(), 2, CentroCuadrillaDos, 0.0f));

	CuadrillaDos.RemoveAll([](AEnemigo* Enemigo) { return Enemigo == nullptr; });

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 12.0f, FColor::Green,
			FString::Printf(TEXT("CUADRILLA 2 desplegada: %d miembros"), CuadrillaDos.Num()));
	}

	UE_LOG(LogTemp, Warning, TEXT("[GameMode] CUADRILLA 2 desplegada con %d miembros"), CuadrillaDos.Num());
}

void ANavesUSFX_022026GameModeBase::VigilarCuadrillaUno()
{
	int32 Vivos = 0;
	for (AEnemigo* Enemigo : CuadrillaUno)
	{
		if (IsValid(Enemigo))
		{
			++Vivos;
		}
	}

	if (GEngine && !bCuadrillaDosDesplegada)
	{
		// Clave fija: el mensaje se reemplaza en lugar de apilarse.
		GEngine->AddOnScreenDebugMessage(200, 1.0f, FColor::Yellow,
			FString::Printf(TEXT("Cuadrilla 1: %d de %d en escena"), Vivos, CuadrillaUno.Num()));
	}

	if (Vivos == 0 && !bCuadrillaDosDesplegada)
	{
		bCuadrillaDosDesplegada = true;
		GetWorldTimerManager().ClearTimer(TemporizadorVigilancia);

		DesplegarCuadrillaDos();
	}
}

AEnemigo* ANavesUSFX_022026GameModeBase::CrearEnemigo(TSubclassOf<AEnemigo> ClaseEnemigo, int32 NumeroCuadrilla,
	const FVector& Centro, float SegundosDeVida)
{
	UWorld* Mundo = GetWorld();
	if (!Mundo || !ClaseEnemigo)
	{
		return nullptr;
	}

	// Spawn diferido: hay que configurar la cuadrilla ANTES de que corra el
	// BeginPlay del enemigo, porque es ahi donde arma su FTimerHandle.
	const FTransform Transformacion(FRotator::ZeroRotator, Centro);

	AEnemigo* Nuevo = Mundo->SpawnActorDeferred<AEnemigo>(ClaseEnemigo, Transformacion);
	if (!Nuevo)
	{
		return nullptr;
	}

	Nuevo->ConfigurarCuadrilla(NumeroCuadrilla, Centro, SegundosDeVida);
	UGameplayStatics::FinishSpawningActor(Nuevo, Transformacion);

	return Nuevo;
}

// ---------------------------------------------------------------------------
//  Escenario
// ---------------------------------------------------------------------------

void ANavesUSFX_022026GameModeBase::PrepararEscenario()
{
	// Terreno general, solido para que el jugador no lo atraviese.
	CrearPlano(FVector(0.0f, 0.0f, 0.0f), FVector(160.0f, 160.0f, 1.0f),
		FLinearColor(0.15f, 0.19f, 0.13f), true);

	// Zona de agua de cada cuadrilla, donde navega la familia acuatica.
	const FVector Desfase = AEnemigoAcuatico::DesfaseDelAgua();

	CrearPlano(CentroCuadrillaUno + Desfase + FVector(0.0f, 0.0f, 15.0f),
		FVector(34.0f, 30.0f, 1.0f), FLinearColor(0.04f, 0.20f, 0.38f), false);

	CrearPlano(CentroCuadrillaDos + Desfase + FVector(0.0f, 0.0f, 15.0f),
		FVector(34.0f, 30.0f, 1.0f), FLinearColor(0.04f, 0.20f, 0.38f), false);
}

void ANavesUSFX_022026GameModeBase::CrearPlano(const FVector& Posicion, const FVector& Escala,
	const FLinearColor& Color, bool bSolido)
{
	UWorld* Mundo = GetWorld();
	if (!Mundo)
	{
		return;
	}

	FActorSpawnParameters Parametros;
	Parametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* Plano = Mundo->SpawnActor<AActor>(AActor::StaticClass(), Posicion, FRotator::ZeroRotator, Parametros);
	if (!Plano)
	{
		return;
	}

	UStaticMeshComponent* Componente = NewObject<UStaticMeshComponent>(Plano);
	Componente->SetMobility(EComponentMobility::Movable);

	if (bSolido)
	{
		Componente->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Componente->SetCollisionProfileName(TEXT("BlockAll"));
	}
	else
	{
		Componente->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (UStaticMesh* MallaPlano = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane.Plane")))
	{
		Componente->SetStaticMesh(MallaPlano);
	}

	if (UMaterial* MaterialBasico = LoadObject<UMaterial>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial")))
	{
		Componente->SetMaterial(0, MaterialBasico);
	}

	Componente->SetRelativeScale3D(Escala);
	Plano->SetRootComponent(Componente);
	Componente->RegisterComponent();

	if (UMaterialInstanceDynamic* Dinamico = Componente->CreateAndSetMaterialInstanceDynamic(0))
	{
		Dinamico->SetVectorParameterValue(TEXT("Color"), Color);
	}
}

void ANavesUSFX_022026GameModeBase::ColocarJugador()
{
	APlayerController* Controlador = UGameplayStatics::GetPlayerController(this, 0);
	if (!Controlador)
	{
		return;
	}

	// Punto de partida: atras y en alto, con las dos zonas de cuadrilla a la vista.
	const FVector PosicionInicial(0.0f, -7000.0f, 2600.0f);
	const FRotator RotacionInicial(-15.0f, 90.0f, 0.0f);

	if (APawn* Jugador = Controlador->GetPawn())
	{
		Jugador->SetActorLocationAndRotation(PosicionInicial, RotacionInicial);
	}

	Controlador->SetControlRotation(RotacionInicial);
	Controlador->bShowMouseCursor = false;
	Controlador->SetInputMode(FInputModeGameOnly());

	MostrarControles();
}

void ANavesUSFX_022026GameModeBase::MostrarControles()
{
	if (!GEngine)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(10, 600.0f, FColor::White, TEXT("ESC  salir"));
	GEngine->AddOnScreenDebugMessage(11, 600.0f, FColor::White, TEXT("Mouse  mirar alrededor"));
	GEngine->AddOnScreenDebugMessage(12, 600.0f, FColor::White, TEXT("Q / Ctrl  bajar"));
	GEngine->AddOnScreenDebugMessage(13, 600.0f, FColor::White, TEXT("E / Espacio  subir"));
	GEngine->AddOnScreenDebugMessage(14, 600.0f, FColor::White, TEXT("W A S D  desplazarse"));
	GEngine->AddOnScreenDebugMessage(15, 600.0f, FColor::Yellow, TEXT("--- CONTROLES ---"));
}
