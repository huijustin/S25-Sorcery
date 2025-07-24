#pragma once
#include "Enchantment.h"

class EnrageEnchantment : public Enchantment {
public:
    EnrageEnchantment(Minion* base);
    int getAttack() const override;
    int getDefense() const override;
};
