#include Ritual.h
#include <iostream>

void Ritual::trigger(std::string eventString) {
    if (eventString == triggerCondition) {
        if (charges >= activationCost) {
            charges -= activationCost;
            executeEffect(); // NEED TO USE CORRECT FNCTION IMPLEMENTATION HERE
        }
    }
}

void Ritual::play() {
    std::cout << getName() << " Ritual is now active." << std::endl;
}

int Ritual::getCost() {
    return cost;
}

int Ritual::getCharges() {
    return charges;
}


