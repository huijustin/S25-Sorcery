#include "Minion.h"
#include <iostream>

void Minion::attack(Minion* targetEntity) {
    std::cout << "Minion attacks another minion!" << std::endl;
}

void Minion::trigger(std::string eventString) {
    std::cout << "Minion triggers on event: " << eventString << std::endl;
}

void Minion::play() {
    std::cout << "Playing Minion card." << std::endl;
}

int Minion::getCost() {
    return 3; // Example cost
}

Enchantment* Minion::topEnchantment() {
    if (!enchantments.empty()) {
        return enchantments.back();
    }
    return nullptr;
}
