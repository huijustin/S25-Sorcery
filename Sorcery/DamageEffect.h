#pragma once
#include "Effect.h"
#include "Minion.h"

class DamageEffect : public Effect {
    Minion* targetEntity;
    int damage;

public:
    DamageEffect(Minion* targetEntity, int damage);
    void apply() override;
};
