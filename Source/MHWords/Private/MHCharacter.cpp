// Fill out your copyright notice in the Description page of Project Settings.


#include "MHCharacter.h"

#include "DelayAction.h"
#include "WeaponComponent.h"
#include "DSP/Delay.h"

AMHCharacter::AMHCharacter()
{
	m_Monster = nullptr;
	bIsFighting = false;
	bFightFinish = true;
}

void AMHCharacter::fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster)
{
	this->m_Monster = monster;
	bFightFinish = false;
}

void AMHCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bFightFinish)
	{
		startFight();
	}
}

void AMHCharacter::fight_()
{
	bIsFighting = true;
	if (this->bloodValue > 0 && m_Monster->bloodValue > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("延迟前"));
		
		UE_LOG(LogTemp, Log, TEXT("延迟后"));
		
		AttackFromType type = AMHCharacterBase::Default;
		const int x = FMath::Min(this->curNatureValue, m_Monster->curNatureValue);
		this->curNatureValue -= x;
		m_Monster->curNatureValue -= x;
		
		if (this->curNatureValue == 0 && m_Monster->curNatureValue == 0)
		{
			this->curNatureValue = this->natureValue;
			m_Monster->curNatureValue = m_Monster->natureValue;
			type = AMHCharacterBase::SameTime;
		}
		else if (this->curNatureValue == 0)
		{
			this->curNatureValue = this->natureValue;
			type = AMHCharacterBase::PlayerToMonster;
		}
		else if (m_Monster->curNatureValue == 0)
		{
			m_Monster->curNatureValue = m_Monster->natureValue;
			type = AMHCharacterBase::MonsterToPlayer;
		}
		
		int rd = FMath::RandRange(0, 100);
		int damaged = 0;
		switch (type)
		{
		case AMHCharacterBase::PlayerToMonster:
			if (rd <= m_Monster->missValue)
			{
				UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(m_Monster->name));
			}
			else
			{
				damaged = this->attackValue - m_Monster->defenseValue;
				m_Monster->bloodValue -= damaged;
				UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(m_Monster->name), m_Monster->bloodValue);
			}
			break;
		case AMHCharacterBase::MonsterToPlayer:
			if (rd <= this->missValue)
			{
				UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(this->name));
			}
			else
			{
				damaged = m_Monster->attackValue - this->defenseValue;
				this->bloodValue -= damaged;
				UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(this->name), this->bloodValue);
			}
			break;
		case AMHCharacterBase::SameTime:
			UE_LOG(LogTemp, Log, TEXT("同时攻击！"));
			rd = FMath::RandRange(0, 100);
			if (rd <= calmValue)
			{
				rd = FMath::RandRange(0, 100);
				if (rd <= this->missValue)
				{
					UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(this->name));
				}
				else
				{
					damaged = m_Monster->attackValue - this->defenseValue;
					this->bloodValue -= damaged;
					UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(this->name), this->bloodValue);
				}
			}
			
			damaged = this->attackValue - m_Monster->defenseValue;
			m_Monster->bloodValue -= damaged;
			UE_LOG(LogTemp, Log, TEXT("%s 剩余血量: %d"), *(m_Monster->name), m_Monster->bloodValue);
			break;
		}
	}
	
	if (this->bloodValue <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 倒下了！！！"), *(this->name));
		UE_LOG(LogTemp, Log, TEXT("失败！！！"));
		bFightFinish = true;
	}
	else if (m_Monster->bloodValue <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 倒下了！！！"), *(m_Monster->name));
		UE_LOG(LogTemp, Log, TEXT("胜利！！！"));
		bFightFinish = true;
	}
	bIsFighting = false;
}

void AMHCharacter::startFight()
{
	if (!bIsFighting)
	{
		if (UWorld* world = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
		{
			FLatentActionManager& LatentActionManager = world->GetLatentActionManager();
			FLatentActionInfo LatentInfo;

			if (this->bloodValue > 0 && m_Monster && m_Monster->bloodValue > 0 && !bFightFinish)
			{
				LatentInfo.CallbackTarget = this;
				LatentInfo.ExecutionFunction = TEXT("fight_");
				LatentInfo.Linkage = 0;
				LatentInfo.UUID = FMath::Rand();
				LatentActionManager.AddNewAction(this, LatentInfo.UUID, new FDelayAction(2.0, LatentInfo));
			}
		}
	}
}
