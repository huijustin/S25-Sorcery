#include <GiantStrengthEnchantment.h>

int GiantStrengthEnchantment::getAttack() const {
    return base->getAttack() + 2;
}

int GiantStrengthEnchantment::getDefense() const {
    return base->getDefense() + 2;
}
