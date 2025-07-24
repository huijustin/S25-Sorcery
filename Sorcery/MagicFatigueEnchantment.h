#pragma once
#include "Enchantment.h"
#include "Ability.h"

class MagicFatigueEnchantment : public Enchantment {
public:
    MagicFatigueEnchantment(Minion* base);
    Ability* getAbility() const override;
};
