// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowerDefenseHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseHUD : public AHUD
{
	GENERATED_BODY()
	
	public:
		ATowerDefenseHUD();

		// Begin HUD interface
		virtual void DrawHUD() override;

		/** current UI scale */
		float UIScale;

	protected:
		/** 
		* Draws health bar for specific actor.
		*
		* @param	ForActor	Actor for which the health bar is for.
		* @param	HealthPercentage	Current Health percentage.
		* @param	BarHeight	Height of the health bar
		* @param	OffsetY		Y Offset of the health bar.
		*/
		void DrawHealthBar(AActor* ForActor, float HealthPercentage, int32 BarHeight, int OffsetY = 0) const;

		/** enemy team health bar texture */
		UPROPERTY()
		class UTexture2D* EnemyTeamHPTexture;

		/** gray health bar texture */
		UPROPERTY()
		class UTexture2D* BarFillTexture;

		/** draw health bars for actors */
		void DrawActorsHealth();
};
