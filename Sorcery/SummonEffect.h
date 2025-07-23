#pragma once
#include "Effect.h"
#include "Minion.h"
#include <vector>

class SummonEffect : public Effect {
    Minion* toSummon; // Pointer to the minion to summon
    int amount;

public:
    SummonEffect(Minion* templateMinion, int amount);
    void apply() override;
};
