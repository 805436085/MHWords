// Fill out your copyright notice in the Description page of Project Settings.


#include "MHCharacter.h"

#include "DelayAction.h"
#include "WeaponComponent.h"
#include "MHMonster.h"
#include "DSP/Delay.h"

#define FreshTime 0.5

AMHCharacter::AMHCharacter()
{
	m_WeaponComponet = nullptr;
	m_Monster = nullptr;
	m_bIsFighting = false;
}

void AMHCharacter::pushMessageToBox_Implementation(const FString& str)
{
	
}

void AMHCharacter::fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster)
{
	AMHMonster* m = dynamic_cast<AMHMonster*>(monster);
	if (m)
	{
		this->m_Monster = m;
		m_bIsFighting = true;
	}
}

void AMHCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	static float DeltaS = 0.0;
	if (m_bIsFighting)
	{
		if (DeltaS < FreshTime)
		{
			DeltaS += DeltaSeconds;
		}
		else if (DeltaS >= FreshTime)
		{
			DeltaS = 0.0;
			fight_();
		}
	}
	else
	{
		DeltaS = 0.0;
	}
}

void AMHCharacter::fight_()
{
	if (this->bloodValue > 0 && m_Monster->bloodValue > 0)
	{
		if (m_WeaponComponet && IsValid(m_WeaponComponet))
		{
			FStringFormatOrderedArguments args;
			FString str;
			
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
					args.Reset();
					args.Add(FStringFormatArg(m_Monster->name));
					str = FString::Format(TEXT("{0} 躲开了！"), args);
					pushMessageToBox(str);
				}
				else
				{
					int tmpAttackValue = m_WeaponComponet->m_AttackValue * m_WeaponComponet->m_XiuzhengValue * m_WeaponComponet->m_ZhanweiValue * m_WeaponComponet->m_ZhaoshiValue * (float)(1 + m_arrayShulianduValue[0] * 0.01);
					int count = m_Monster->m_HitPos.Num();
					int weightSum = 0;
					
					for(int i = 0; i < count; i++)
					{
						weightSum += m_Monster->m_HitPos[i].weight;
					}
					rd = FMath::RandRange(1, weightSum);

					FString hitstr;
					for(int i = 0; i < count; i++)
					{
						rd -= m_Monster->m_HitPos[i].weight;
						if (rd <= 0)
						{
							hitstr = m_Monster->m_HitPos[i].name;
							m_Monster->m_RouZhi = m_Monster->m_HitPos[i].defenseRatio;
							break;
						}
					}
					
					damaged = tmpAttackValue - m_Monster->defenseValue * m_Monster->m_RouZhi;
					m_Monster->bloodValue -= damaged;
					UE_LOG(LogTemp, Log, TEXT("命中%s的%s 剩余血量: %d"), *(m_Monster->name), *(hitstr), m_Monster->bloodValue);
					args.Reset();
					args.Add(FStringFormatArg(m_Monster->name));
					args.Add(FStringFormatArg(m_Monster->bloodValue));
					str = FString::Format(TEXT("{0} 剩余血量: {1}"), args);
					pushMessageToBox(str);
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
			m_bIsFighting = false;
		}
		else if (m_Monster->bloodValue <= 0)
		{
			UE_LOG(LogTemp, Log, TEXT("%s 倒下了！！！"), *(m_Monster->name));
			UE_LOG(LogTemp, Log, TEXT("胜利！！！"));
			m_bIsFighting = false;
		}
	}
}

void AMHCharacter::startFight()
{
	if (UWorld* world = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& LatentActionManager = world->GetLatentActionManager();
		FLatentActionInfo LatentInfo;

		if (this->bloodValue > 0 && m_Monster && m_Monster->bloodValue > 0)
		{
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = TEXT("fight_");
			LatentInfo.Linkage = 0;
			LatentInfo.UUID = FMath::Rand();
			LatentActionManager.AddNewAction(this, LatentInfo.UUID, new FDelayAction(0.1, LatentInfo));
		}
	}
}
