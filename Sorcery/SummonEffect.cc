#include "SummonEffect.h"
#include <iostream>

SummonEffect::SummonEffect(Minion* toSummon, int amount)
    : toSummon(toSummon), amount(amount) {}

void SummonEffect::apply() {
    if (!toSummon) {
        std::cerr << "No summon provided" << std::endl;
        return;
    }

    std::cout << "Summoning " << amount << " " << toSummon->getName() << std::endl;

    for (int i = 0; i < amount; ++i) {
        Minion* copy = new Minion(*toSummon);  // Copy constructor used to clone the minion

        // Some code to put the minion onto the board in the correct spot

        std::cout << "Summoned " << copy->getName() << std::endl;
    }
}

// Create overload for summoning from graveyard
