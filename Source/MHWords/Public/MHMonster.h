// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MHCharacterBase.h"
#include "MHMonster.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FHitPosStruct
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	float defenseRatio;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	int weight;
};

UCLASS()
class MHWORDS_API AMHMonster : public AMHCharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	float m_RouZhi;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	TArray<FHitPosStruct> m_HitPos;
};
