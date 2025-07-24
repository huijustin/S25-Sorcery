#include "EnrageEnchantment.h"

EnrageEnchantment::EnrageEnchantment(Minion* base)
    : Enchantment(base) {}

int EnrageEnchantment::getAttack() const {
    return base->getAttack() * 2;
}

int EnrageEnchantment::getDefence() const {
    return base->getDefence() * 2;
}
