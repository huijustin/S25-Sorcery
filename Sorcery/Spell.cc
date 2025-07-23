#include Spell.h
#include <iostream>

void Spell::play() {

    executeEffect(); // CHECK WITH GROUP
    // Executes the spells effect

    std::cout << getName() << " spell cast." << std::endl; // Check output with Group
}

int Spell::getCost() {
    return cost;
}

void Spell:activate() { // CHECK WHAT ACTIVATE DOES WITH GROUP
    std::cout << "Spell effect activated" << std::endl;
}