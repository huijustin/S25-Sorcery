#include "Minion.h"
#include <iostream>

Minion::Minion(int ID, std::string name, int cost, int atk, int def)
    : Card(ID, std::move(name), cost), attack(atk), defense(def), actions(0) {}

void Minion::attackTarget(Minion* targetEntity) {
    if (actions <= 0) { return }

    if (!targetEntity) {
        std::cerr << "Error: No Target." << std::endl;
        return;
    }

    // Damage handling
    std::cout << getName() << " deals " << getAttack() << " damage to " << targetEntity->getName() << std::endl;
    std::cout << targetEntity->getName() << " deals " << targetEntity->getAttack() << " damage to " << getName() << std::endl;
    targetEntity->takeDamage(attack);
    takeDamage(targetEntity->getAttack());

    setActions(0);
}

void Minion::takeDamage(int dmg) {
    defense -= dmg;

    if (defense <= 0) {
        std::cout << getName() << " has been destroyed!" << std::endl;
        // move minion to graveyard and Trigger observer
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
