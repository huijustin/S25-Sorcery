#include "DarkRitual.h"
#include <iostream>

DarkRitual::DarkRitual()
    : Ritual(19, "Dark Ritual", 1, "Start of Turn", 5) {} // ID, name, cost, trigger, charges

std::unique_ptr<Card> DarkRitual::clone() const {
    return std::make_unique<DarkRitual>(*this);
}

void DarkRitual::trigger(const std::string& triggerString, Player* player) {
    if (triggerString == "Start of Turn" && charges > 0 && player) {
        player->gainMagic(1);  
        std::cout << "Dark Ritual triggers: " << player->getName() << " gains +1 magic." << std::endl;
    }
}
