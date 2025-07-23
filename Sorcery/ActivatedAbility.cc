#include "ActivatedAbility.h"
#include <iostream>

ActivatedAbility::ActivatedAbility(int cost, std::string description, Effect* effect)
    : cost(cost), description(std::move(description)), effect(effect) {}

void ActivatedAbility::useEffect() {
    std::cout << "Activated: " << description << std::endl;

    effect->apply();

    // Code to spend mana from player
}

std::string ActivatedAbility::getDescription() const {
    return description;
}

int ActivatedAbility::getActivationCost() const {
    return cost;
}
