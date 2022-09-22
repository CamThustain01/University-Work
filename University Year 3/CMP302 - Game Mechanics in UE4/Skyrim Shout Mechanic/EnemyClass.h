// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPcharComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Character.h"
#include "EnemyClass.generated.h"

UCLASS(Blueprintable)
class GRAVITYGUN_API AEnemyClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyClass();

	UPROPERTY()
	UGameplayStatics* gameplayStatics; //gameplay statics pointer

	UFUNCTION(BlueprintCallable)
		void Shout_Collision_Response(); //enemies collision response to shout

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float m_vector_offset = 15000.0f; //vector offset value for calculating impulse
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
