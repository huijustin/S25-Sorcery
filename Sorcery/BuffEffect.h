#pragma once
#include "Effect.h"
#include <functional>

class Minion;

class BuffEffect : public Effect {
    Minion** targetSlot;  // Pointer to a pointer to minion(from game logic)
    std::function<Minion*(Minion*)> enchantmentApplicator;  // function that returns new Enchantment*

public:
    BuffEffect(Minion** targetSlot, std::function<Minion*(Minion*)> enchantmentApplicator);

    bool supportsTarget() const override { return true; }
    void setTarget(Minion* target) override;
    void apply() override;
    std::unique_ptr<Effect> clone() const override;
};
