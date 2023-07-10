// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if(shooterCharacter == nullptr)
	{
		shooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if(shooterCharacter)
	{
		// Get the lateral speed of the character from velocity
		FVector Velocity = shooterCharacter->GetVelocity();
		Velocity.Z = 0;
		// Size() is the magnitude of velocity vector
		Speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = shooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating
		if(shooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = shooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(shooterCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if(shooterCharacter->GetVelocity().Size() > 0.f)
		{
			lastMovementOffsetYaw = MovementOffsetYaw;
		}
		//FString RotationMessage = FString::Printf(TEXT("Base Aim Rotation: %f"), AimRotation.Yaw);
		//FString MovementRotationMessage = FString::Printf(TEXT("Movement Rotation: %f"), 
		//	MovementRotation.Yaw);
		//FString OffsetMessage = FString::Printf(TEXT("Movement Offset Yaw: %f"), MovementOffsetYaw);
		//if(GEngine)
		//{
		//	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, OffsetMessage);
		//}
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	shooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
