// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenseHUD.h"

#include "AICharacter.h"
#include "CanvasItem.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"

ATowerDefenseHUD::ATowerDefenseHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("/Game/UI/HUD/BarFill"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> EnemyTeamHPObj(TEXT("/Game/UI/HUD/EnemyTeamHealthBar"));
	EnemyTeamHPTexture = EnemyTeamHPObj.Object;
	BarFillTexture = BarFillObj.Object;
}


/**
 * This is the main drawing pump.  It will determine which hud we need to draw (Game or PostGame).  Any drawing that should occur
 * regardless of the game state should go here.
 */
void ATowerDefenseHUD::DrawHUD()
{


	if ( GEngine && GEngine->GameViewport )
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		UIScale = ViewportSize.X / 2048.0f;
	}

	Super::DrawHUD();
	bool bConsoleOpen = false;
	DrawActorsHealth();
}

void ATowerDefenseHUD::DrawHealthBar(AActor* ForActor, float HealthPercentage, int32 BarHeight, int OffsetY) const
{
	FBox BB = ForActor->GetComponentsBoundingBox();
	FVector Center = BB.GetCenter();
	FVector Extent = BB.GetExtent();
	FVector2D Center2D = FVector2D(Canvas->Project(FVector(Center.X,Center.Y,Center.Z + Extent.Z)));
	float ActorExtent = 40;
	if (Cast<APawn>(ForActor) != NULL)
	{
		AAICharacter* StrategyChar = Cast<AAICharacter>(ForActor);
		if( ( StrategyChar != NULL ) && ( StrategyChar->GetCapsuleComponent() != NULL ) )
		{
			ActorExtent = StrategyChar->GetCapsuleComponent()->GetScaledCapsuleRadius();
		}
	}

	FVector Pos1 = Canvas->Project(FVector(Center.X,Center.Y - ActorExtent*2, Center.Z + Extent.Z));
	FVector Pos2 = Canvas->Project(FVector(Center.X,Center.Y + ActorExtent*2, Center.Z + Extent.Z));
	float HealthBarLength = (Pos2-Pos1).Size2D();

	UTexture2D* HealthBarTexture = EnemyTeamHPTexture;

	float X = Center2D.X - HealthBarLength/2;
	float Y = Center2D.Y + OffsetY;
	FCanvasTileItem TileItem( FVector2D( X, Y ), HealthBarTexture->Resource, FVector2D( HealthBarLength * HealthPercentage,  BarHeight ), FLinearColor::White );
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.UV1 = FVector2D(HealthPercentage, 1.0f);

	Canvas->DrawItem( TileItem );
	//Fill the rest of health with gray gradient texture
	X = Center2D.X-HealthBarLength/2 + HealthBarLength * HealthPercentage;
	Y = Center2D.Y + OffsetY;
	TileItem.Position = FVector2D( X, Y );
	TileItem.Texture = BarFillTexture->Resource;
	TileItem.UV1 = FVector2D(1.0f, 1.0f);
	TileItem.Size = FVector2D( HealthBarLength * (1.0f - HealthPercentage), BarHeight );
	TileItem.SetColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
	Canvas->DrawItem( TileItem );	
}

void ATowerDefenseHUD::DrawActorsHealth()
{
	for (AAICharacter* TestChar : TActorRange<AAICharacter>(GetWorld()))
	{
		if (TestChar->GetHealth() > 0)
		{
			DrawHealthBar(TestChar,TestChar->GetHealth()/(float)TestChar->GetMaxHealth(),18*UIScale);
		}
	}
}

