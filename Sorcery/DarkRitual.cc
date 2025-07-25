#include "DarkRitual.h"
#include <iostream>

DarkRitual::DarkRitual()
    : Ritual(19,"Dark Ritual",0,"Gain 1 magic each turn",1,5,"Start of Turn") {}


std::unique_ptr<Card> DarkRitual::clone() const {
    return std::make_unique<DarkRitual>(*this);
}

void DarkRitual::trigger(const std::string& triggerString, Player* player) {
    if (triggerString == "Start of Turn" && charges > 0 && player) {
        player->gainMagic(1);  
        std::cout << "Dark Ritual triggers: " << player->getName() << " gains +1 magic." << std::endl;
    }
}
