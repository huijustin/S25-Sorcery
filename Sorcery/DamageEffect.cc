#include "DamageEffect.h"
#include <iostream>

DamageEffect::DamageEffect(Minion* targetEntity, int damage)
    : targetEntity(targetEntity), damage(damage) {}

void DamageEffect::apply() {
    if (!targetEntity) {
        std::cerr << "Error: No target" << std::endl;
        return;
    }

    std::cout << targetEntity->getName() << " takes " << damage << " damage!" << std::endl;
    targetEntity->takeDamage(damage);
}
