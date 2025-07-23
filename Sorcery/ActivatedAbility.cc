#include "ActivatedAbility.h"
#include <iostream>

ActivatedAbility::ActivatedAbility(int cost, std::string description, std::unique_ptr<Effect> effect)
    : cost(cost), description(std::move(description)), effect(std::move(effect)) {}

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

std::string ActivatedAbility::getDescription() const {
    return description;
}

int ActivatedAbility::getActivationCost() const {
    return cost;
}
