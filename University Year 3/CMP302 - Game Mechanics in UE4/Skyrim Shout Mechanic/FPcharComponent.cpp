// Fill out your copyright notice in the Description page of Project Settings.


#include "FPcharComponent.h"

// Sets default values
AFPcharComponent::AFPcharComponent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPcharComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPcharComponent::ShoutMechanic()
{
	if (m_moving) //first check, is the player moving?
	{
		if (m_mana >= m_shout_cost) //second check, is the players mana greater or equal to the cost of the spell
		{ //if yes to both....

			FVector start_ = GetActorLocation();// create a vector for line trace first parameter "start", gets actor location
			FVector vector_ = UKismetMathLibrary::GetForwardVector(GetControlRotation()) * 4000.0; //create a forward vector for the end vector, use control rotation as rotator and multiply by offset of 4000
			FVector end_ = start_ + vector_; //create end vector for line trace function, start vector + forward vector.
			TArray<FHitResult> OutHit;//an array of hit results called out hit since using multi line trace function
	

			dummy = 1.0; //changes dummy variable for testing 

			if (GetWorld()->LineTraceMultiByChannel(OutHit, start_, end_, ECC_Visibility))//checks if there is a line trace.
			{
				dummy = 2.0;//sets dummy to 2 for testing purposes 

				for (auto it : OutHit) //iterates through everything thats been hit by line trace
				{ 
					dummy = 3.0; //sets dummy to 3 for testing purposes 

					if (!it.GetActor()->ActorHasTag(FName("Pushable"))) //checks each iteration and if it has the tag "Pushable" do the following...
					{

						dummy = 4.0;//set dummy to 4.0 for testing...
						continue; //continue
					}

					auto* enemyptr = Cast<AEnemyClass>(it.GetActor()); //create a cast to enemy class 
					//auto* enemyptr = (AEnemyClass*)(it.GetActor()); // either work

					if (!enemyptr) //if the cass isnt null continue ... error check
					{
						dummy =  5.0;
						continue;
					}

					if (m_mana > 0.0)//if mana is greate that 0.0
					{
						dummy = 6.0;
						enemyptr->Shout_Collision_Response(); //call enemies collision response function
						m_mana -= m_shout_cost; //take away shout cost from mana.
					}
				}
			}

			
		}

	}
}

void AFPcharComponent::ManaRecharge()
{
	if (m_mana_timer >= m_mana_charge_rate) //if mana timer is greater than or equal to mana charge rate...
	{
		if (m_mana < 1.0) //check if mana is less than 1.0
		{
			m_mana += m_mana_regen; //if so add mana regen value to mana

			if (m_mana > 1.0) //if mana is over 1 
			{
				m_mana = 1.0; //set mana to 1 , checks so mana cant "overflow"
			}
		}

		m_mana_timer = 0.0f; //set mana timer to 0.0 again.
	}
}

// Called every frame
void AFPcharComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Called to bind functionality to input
void AFPcharComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



