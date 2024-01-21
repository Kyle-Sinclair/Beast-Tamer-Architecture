#pragma once
#include "MoveData.h"
#include "RawTypeEffectData.h"

class CombatHelpers
{
public:
    static unsigned int CalculateAbilityDamage(RawTypeEffectData attacker, RawTypeEffectData defender,MoveData data);
};
