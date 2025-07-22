#include "Spell.h"
#include <iostream>


Spell::Spell(int cost) : Card(cost) {}

void Spell::activate() {
    std::cout << "Activating Spell effect." << std::endl;
}

void Spell::play() {
    std::cout << "Playing Spell card. Cost: " << cost << std::endl;
    activate();
}
