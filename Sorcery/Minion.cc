#include "Minion.h"
#include <iostream>

Minion::Minion(int ID, std::string name, int cost, int atk, int def)
    : Card(ID, std::move(name), cost), attack(atk), defense(def), actions(0) {}

void Minion::attackTarget(Minion* targetEntity) {
    std::cout << "Minion attacks another minion!" << std::endl;
}

void Minion::trigger(const std::string& eventString) {
    std::cout << "Minion triggers on event: " << eventString << std::endl;
}

void Minion::play() {
    std::cout << "Playing Minion card." << std::endl;
}

Enchantment* Minion::topEnchantment() {
    if (!enchantments.empty()) {
        return enchantments.back();
    }
    return nullptr;
}

int Minion::getAttack() const {
    return attack;
}

int Minion::getDefense() const {
    return defense;
}

int Minion::getActions() const {
    return actions;
}

void Minion::setActions(int a) {
    actions = a;
}
