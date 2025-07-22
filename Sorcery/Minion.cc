#include "Minion.h"
#include <iostream>

Minion::Minion(int ID, std::string name, int cost, int atk, int def)
    : Card(ID, std::move(name), cost), attack(atk), defense(def), actions(0) {}

void Minion::attackTarget(Minion* targetEntity) {
    if (!targetEntity) {
        std::cerr << "Error: No Target." << std::endl;
        return;
    }

    std::cout << getName() << " attacks " << targetEntity->getName() << " dealing " << attack << " damage."<< std::endl;
    targetEntity->takeDamage(attack);
}

void Minion::takeDamage(int dmg) {
    defense -= dmg;

    if (defense <= 0) {
        std::cout << getName() << " has been destroyed!" << std::endl;
        // destroy minion and Trigger observer
    }
}

void Minion::trigger(const std::string& eventString) {
    std::cout << "Minion triggers event: " << eventString << std::endl;
}

void Minion::play() {
    std::cout << "Playing " << getName() << "." << std::endl;
}

Enchantment* Minion::topEnchantment() {
    if (!enchantments.empty()) {
        return enchantments.back();
    }
    return nullptr;
}
int Minion::getAttack() const { return attack; }
int Minion::getDefense() const { return defense; }
int Minion::getActions() const { return actions; }
void Minion::setActions(int a) { actions = a; }
