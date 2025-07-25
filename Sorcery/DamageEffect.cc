#include "DamageEffect.h"
#include <iostream>
#include "Minion.h"

DamageEffect::DamageEffect(int damage)
    : targetEntity(nullptr), damage(damage) {}

bool DamageEffect::supportsTarget() const {
    return true;
}

void DamageEffect::setTarget(Minion* target) {
    targetEntity = target;
}

void DamageEffect::apply() {

    if (!targetEntity) {
        std::cerr << "Error: No target" << std::endl;
        return;
    }

    std::cout << targetEntity->getName() << " takes " << damage << " damage!" << std::endl;
    targetEntity->takeDamage(damage);
}

std::unique_ptr<Effect> DamageEffect::clone() const {
    return std::make_unique<DamageEffect>(*this);
}


