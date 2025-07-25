#pragma once
#include "Effect.h"
#include "Minion.h"

class DamageEffect : public Effect {
    Minion* targetEntity = nullptr;
    int damage;

public:
    DamageEffect(int dmg);
    void apply() override;
    void setTarget(Minion* t) override;
    bool supportsTarget() const override;
    std::unique_ptr<Effect> clone() const override;

};
