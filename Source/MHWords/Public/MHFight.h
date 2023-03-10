#pragma once
#include "MHFightInterface.h"
#include "MHFight.generated.h"

UCLASS()
class MHWORDS_API UMHFight : public UObject, public IMHFightInterface
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
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void fight(AMHCharacterBase* player, AMHCharacterBase* monster);
    virtual void fight_Implementation(AMHCharacterBase* player, AMHCharacterBase* monster) override;
    //void fight(AMHCharacterBase* player, AMHCharacterBase* monster);
};

