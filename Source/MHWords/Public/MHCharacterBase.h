// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MHCharacterBase.generated.h"

UCLASS()
class MHWORDS_API AMHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMHCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "property")
		int bloodValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "property")
		int tiliValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "property")
		int natureValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "property")
		int attackValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "property")
		int defenseValue;
};
