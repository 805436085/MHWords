// Fill out your copyright notice in the Description page of Project Settings.


#include "MHCharacterBase.h"

// Sets default values
AMHCharacterBase::AMHCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMHCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMHCharacterBase::fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster)
{
	return ;
	
	int a = player->natureValue;
	int b = monster->natureValue;
	while (player->bloodValue > 0 && monster->bloodValue > 0)
	{
		AttackFromType type = AttackFromType::Default;
		const int x = FMath::Min(a, b);
		UE_LOG(LogTemp, Log, TEXT("%d"), x);
		UE_LOG(LogTemp, Log, TEXT("%d"), a);
		UE_LOG(LogTemp, Log, TEXT("%d"), b);
		a -= x;
		b -= x;
		
		if (a == 0 && b == 0)
		{
			a = player->natureValue;
			b = monster->natureValue;
			type = AttackFromType::SameTime;
		}
		else if (a == 0)
		{
			a = player->natureValue;
			type = AttackFromType::PlayerToMonster;
		}
		else if (b == 0)
		{
			b = monster->natureValue;
			type = AttackFromType::MonsterToPlayer;
		}

		int rd = FMath::RandRange(0, 100);
		int damaged = 0;
		switch (type)
		{
		case AttackFromType::PlayerToMonster:
			if (rd <= monster->missValue)
			{
				UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(monster->name));
			}
			else
			{
				damaged = player->attackValue - monster->defenseValue;
				monster->bloodValue -= damaged;
				UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(monster->name), monster->bloodValue);
			}
			break;
		case AttackFromType::MonsterToPlayer:
			if (rd <= player->missValue)
			{
				UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(player->name));
			}
			else
			{
				damaged = monster->attackValue - player->defenseValue;
				player->bloodValue -= damaged;
				UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(player->name), player->bloodValue);
			}
			break;
		case AttackFromType::SameTime:
			UE_LOG(LogTemp, Log, TEXT("同时攻击！"));
			rd = FMath::RandRange(0, 100);
			if (rd <= calmValue)
			{
				rd = FMath::RandRange(0, 100);
				if (rd <= player->missValue)
				{
					UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(player->name));
				}
				else
				{
					damaged = monster->attackValue - player->defenseValue;
					player->bloodValue -= damaged;
					UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(player->name), player->bloodValue);
				}
			}
			
			damaged = player->attackValue - monster->defenseValue;
			monster->bloodValue -= damaged;
			UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(monster->name), monster->bloodValue);
			break;
		}
	}
	
	if (player->bloodValue <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 倒下了！！！"), *(player->name));
		UE_LOG(LogTemp, Log, TEXT("失败！！！"));
	}
	else if (monster->bloodValue <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 倒下了！！！"), *(monster->name));
		UE_LOG(LogTemp, Log, TEXT("胜利！！！"));
	}
}
