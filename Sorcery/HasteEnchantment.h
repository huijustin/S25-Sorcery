#pragma once
#include "Enchantment.h"

class HasteEnchantment : public Enchantment {
public:
    HasteEnchantment(Minion* baseMinion);
    ~HasteEnchantment() override = default;
    
    void roundStart() override;
};
