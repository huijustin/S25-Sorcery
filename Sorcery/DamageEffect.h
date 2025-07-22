#pragma once
#include "Effect.h"
#include "Minion.h"

/*
Should not use targetEntity in the construction of the effect
targetEntity should be handled during apply()
*/
class DamageEffect : public Effect {
    Minion* targetEntity; 
    int damage;

public:
    DamageEffect(int damage);

    void selectTarget(Minion* target);

    void apply() override;
};
