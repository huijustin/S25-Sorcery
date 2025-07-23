#include "ActivatedAbility.h"
#include <iostream>

ActivatedAbility::ActivatedAbility(int cost, std::string description, std::unique_ptr<Effect> effect)
    : Ability(std::move(effect), std::move(description)), cost(cost) {}

void ActivatedAbility::useEffect(Minion* target) {
    std::cout << "ActivatedAbility: " << description << std::endl;

    if (effect) {
        // Set target if one is required
        if (effect->supportsTarget()) {
            effect->setTarget(target);
        }
        effect->apply();
    } else {
        std::cerr << "Error: Ability has no effect" << std::endl;
    }
}

int ActivatedAbility::getActivationCost() const {
    return cost;
}
