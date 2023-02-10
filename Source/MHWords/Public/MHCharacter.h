// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MHCharacterBase.h"
#include "MHCharacter.generated.h"


class UWeaponComponent;
/**
 * 
 */
UCLASS()
class MHWORDS_API AMHCharacter : public AMHCharacterBase
{
	GENERATED_BODY()


public:
	virtual void fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	UWeaponComponent* m_WeaponComponet;
};
