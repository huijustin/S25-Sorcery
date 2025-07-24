#pragma once
#include "Enchantment.h"

class GiantStrengthEnchantment : public Enchantment {
public:
    GiantStrengthEnchantment(Minion* baseMinion);
    
    int getAttack() const override;
    int getDefence() const override;
};
