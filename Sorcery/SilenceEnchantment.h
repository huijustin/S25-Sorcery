#pragma once
#include "Enchantment.h"

class SilenceEnchantment : public Enchantment {
public:
    SilenceEnchantment(Minion* baseMinion);
    ~SilenceEnchantment() override = default;
    
    Ability* getAbility() const override;
    void useAbility(Minion* target = nullptr, Board* board = nullptr) override;
};
