// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MHCharacterBase.h"
#include "MHCharacter.generated.h"


class UWeaponComponent;
class AMHMonster;
/**
 * 
 */
UCLASS()
class MHWORDS_API AMHCharacter : public AMHCharacterBase
{
	GENERATED_BODY()

public:
	AMHCharacter();
	virtual void fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void pushMessageToBox(const FString& str);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	UWeaponComponent* m_WeaponComponet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	AMHMonster* m_Monster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	TArray<float> m_arrayShulianduValue;
	
private:
	UFUNCTION()
	void fight_();

	UFUNCTION()
	void startFight();

	bool m_bIsFighting;
};
