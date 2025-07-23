#include "DamageEffect.h"
#include <iostream>

DamageEffect::DamageEffect(int damage)
    : targetEntity(nullptr), damage(damage) {}

void DamageEffect::selectTarget(Minion* target) {
    targetEntity = target;
}

void DamageEffect::apply() {

    // TODO: Asks for target
    selectTarget(nullptr); // changes target to selected

    if (!targetEntity) {
        std::cerr << "Error: No target" << std::endl;
        return;
    }

    std::cout << targetEntity->getName() << " takes " << damage << " damage!" << std::endl;
    targetEntity->takeDamage(damage);
}
