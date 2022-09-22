// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyClass.h"


// Sets default values
AEnemyClass::AEnemyClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("Pushable"));//adds tag to enemies "Pushable"
	
}

void AEnemyClass::Shout_Collision_Response()
{
	

	GetMesh()->SetCollisionProfileName("Ragdoll"); //set enemies collision profile to ragdoll 
	GetMesh()->SetSimulatePhysics(true); //sets phyiscs of enemies to true .

	//auto* playerptr = Cast<AFPcharComponent>(gameplayStatics->GetPlayerCharacter(GetWorld(), 0));
	auto* playerptr = (AFPcharComponent*)(gameplayStatics->GetPlayerCharacter(GetWorld(), 0)); //create a cast to player class get the player character

	if (playerptr == nullptr) //if the cast is null return
	{
		return;
	}

	playerptr->GetControlRotation();//get the player control rotation
	
	FVector impulse_;//create a vector called impulse
	impulse_ = UKismetMathLibrary::GetForwardVector(playerptr->GetControlRotation()) * m_vector_offset; //set impulser to a forward vector of the player control rotation multiplied by the vector offset variable

	GetMesh()->AddImpulse(impulse_,NAME_None,true); //add impulse to mesh
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);//set collision enable for enemy.
	
}

// Called when the game starts or when spawned
void AEnemyClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

