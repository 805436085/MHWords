#include "MHFight.h"
//#include "Math\UnrealMathUtility.h"

void UMHFight::fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster)
{
	int a = player->natureValue;
	int b = monster->natureValue;
	while (player->bloodValue > 0 && monster->bloodValue > 0)
	{
		AttackFromType type = AttackFromType::Default;
		int x = FMath::Min(a, b);
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

		
	}
}