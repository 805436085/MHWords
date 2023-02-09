// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MHFightInterface.h"
#include "MHCharacterBase.generated.h"

UCLASS()
class MHWORDS_API AMHCharacterBase : public ACharacter, public IMHFightInterface
{
	GENERATED_BODY()

	enum AttackFromType
	{
		Default = 0,
		PlayerToMonster = 1,
		MonsterToPlayer = 2,
		SameTime = 3,
		Max
	};

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

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void fight(AMHCharacterBase* player, AMHCharacterBase* monster);
	virtual void fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
		FString name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
		int bloodValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
		int tiliValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
		int natureValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
		int attackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
		int defenseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
		int missValue;
};
