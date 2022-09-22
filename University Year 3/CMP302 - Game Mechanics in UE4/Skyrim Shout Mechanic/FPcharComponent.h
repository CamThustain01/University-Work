// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyClass.h"
#include "Containers/Array.h"
#include "Engine/LatentActionManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "FPcharComponent.generated.h"

UCLASS(Blueprintable)
class GRAVITYGUN_API AFPcharComponent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPcharComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY()
	UKismetMathLibrary* kismetMLib; //pointer for Kismet Math Library


	//Variables for mechanic
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_mana = 1.0; //mana variable set to 1 initially 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_shout_cost = 0.25; //spell cost , 0.25 mana
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_mana_regen = 0.02; //mana regen rate, 0.02
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_mana_charge_rate = 0.5;//mana charge rate 0.5
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_moving = false; //moving variable for checking if player moves
	UPROPERTY(EditAnywhere)
		float m_mana_timer = 0.0f; //mana timer for recharging mana

	//dummy testing variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dummy = 0.0f; //dummy variable for testing purposes

	//Functions for mechanic
	UFUNCTION(BlueprintCallable)
		void ShoutMechanic(); //shout mechanic
	UFUNCTION(BlueprintCallable)
		void ManaRecharge(); //mana system


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
