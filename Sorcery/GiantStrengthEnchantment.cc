#include "GiantStrengthEnchantment.h"

GiantStrengthEnchantment::GiantStrengthEnchantment(Minion* baseMinion)
    : Enchantment(baseMinion) {}

int GiantStrengthEnchantment::getAttack() const {
    return base->getAttack() + 2;
}

int GiantStrengthEnchantment::getDefence() const {
    return base->getDefence() + 2;
}
