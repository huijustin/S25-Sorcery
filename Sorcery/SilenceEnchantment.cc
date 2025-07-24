#include "SilenceEnchantment.h"
#include <iostream>

SilenceEnchantment::SilenceEnchantment(Minion* base)
    : Enchantment(base) {
    std::cout << getName() << " is Silenced! It can't use its ability." << std::endl;
}

Ability* SilenceEnchantment::getAbility() const {
    return nullptr;
}

void SilenceEnchantment::useAbility(Minion* target, Board* board) {
    std::cout << getName() << " is Silenced! It can't use its ability." << std::endl;
}
