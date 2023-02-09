#include "MHFight.h"
//#include "Math\UnrealMathUtility.h"
#include "MHCharacterBase.h"

void UMHFight::fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster)
{
	int a = player->natureValue;
	int b = monster->natureValue;
	while (player->bloodValue > 0 && monster->bloodValue > 0)
	{
		AttackFromType type = AttackFromType::Default;
		const int x = FMath::Min(a, b);
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
			damaged = player->attackValue - monster->defenseValue;
			monster->bloodValue -= damaged;
			break;
		case AttackFromType::MonsterToPlayer:
			if (rd <= player->missValue)
			{
				UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(player->name));
			}
			damaged = monster->attackValue - player->defenseValue;
			player->bloodValue -= damaged;
			break;
		case AttackFromType::SameTime:
				UE_LOG(LogTemp, Log, TEXT("同时攻击！"));
			break;
		}
	}
}

/*
void UMHFight::fight(AMHCharacterBase* player, AMHCharacterBase* monster)
{
	int a = player->natureValue;
	int b = monster->natureValue;
	while (player->bloodValue > 0 && monster->bloodValue > 0)
	{
		AttackFromType type = AttackFromType::Default;
		const int x = FMath::Min(a, b);
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
			damaged = player->attackValue - monster->defenseValue;
			monster->bloodValue -= damaged;
			break;
		case AttackFromType::MonsterToPlayer:
			if (rd <= player->missValue)
			{
				UE_LOG(LogTemp, Log, TEXT("%s 躲开了！"), *(player->name));
			}
			damaged = monster->attackValue - player->defenseValue;
			player->bloodValue -= damaged;
			break;
		case AttackFromType::SameTime:
			UE_LOG(LogTemp, Log, TEXT("同时攻击！"));
			break;
		}
	}
}
*/