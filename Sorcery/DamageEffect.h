#pragma once
#include "Effect.h"
class Minion;

class DamageEffect : public Effect {
    Minion* targetEntity = nullptr;
    int damage;

public:
    DamageEffect(int dmg);
    void apply() override;
    void setTarget(Minion* t) override;
    bool supportsTarget() const override;
    virtual std::unique_ptr<Effect> clone() const = 0;

};
