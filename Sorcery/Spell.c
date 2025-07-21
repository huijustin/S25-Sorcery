#include "Spell.h"
#include <iostream>

void Spell::activate() {
    std::cout << "Activating Spell effect." << std::endl;
}

void Spell::play() {
    std::cout << "Playing Spell card." << std::endl;
    activate();
}

int Spell::getCost() {
    return 2; // Example cost
}
