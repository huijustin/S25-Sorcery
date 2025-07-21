#pragma once
#include "Ability.h"
#include "Minion.h"

class SummonAbility : public Ability {
    int minionsSummoned;
public:
    void useEffect(Minion* summonedMinion);
};
