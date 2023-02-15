// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MHWORDS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	float m_AttackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	float m_ZhanweiValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	float m_XiuzhengValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "property")
	float m_ZhaoshiValue;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
