#include "Minion.h"
#include <iostream>

Minion::Minion(int ID, std::string name, int cost, int atk, int def, Ability* ability, std::string cardText)
    : Card(ID, std::move(name), cost, std::move(cardText)), // Card attributes
      attack(atk), defense(def), actions(0), ability(ability) {} // Minion attributes

void Minion::attackMinion(Minion* targetMinion) {
    if (actions <= 0) { return; }

    if (!targetMinion) {
        std::cerr << "Error: No Minion." << std::endl;
        return;
    }

    // Damage handling
    std::cout << getName() << " deals " << getAttack() << " damage to " << targetMinion->getName() << std::endl;
    std::cout << targetMinion->getName() << " deals " << targetMinion->getAttack() << " damage to " << getName() << std::endl;
    targetMinion->takeDamage(getAttack());
    takeDamage(targetMinion->getAttack());

    setActions(0);
}

void Minion::attackPlayer(Player* targetPlayer) {
    if (!targetPlayer) {
        std::cerr << "Error: Null player." << std::endl;
        return;
    }

    std::cout << getName() << " deals "  << getAttack()  << " damage to " << targetPlayer->getName() << std::endl;
    targetPlayer->takeDamage(getAttack());
}

void Minion::takeDamage(int dmg) {
    defense -= dmg;

    if (defense <= 0) {
        std::cout << getName() << " has been destroyed!" << std::endl;

        // Trigger observer to move minion to graveyard
    }
}

void Minion::trigger(const std::string& eventString) {
    std::cout << "Trigger some event: " << eventString << std::endl;
}

void Minion::play() {
    std::cout << "Playing " << getName() << "." << std::endl;
}

void Minion::useAbility() {
    if (getAbility()) {
        // If ability requires a target
        if (getAbility()->getEffect()->supportsTarget()) {
            Minion* chosenTarget = nullptr; 
            
            // TODO: Implement a way to select target
            
            getAbility()->useEffect(chosenTarget);
        }
        else {
            getAbility()->useEffect();
        }
        std::cout << getName() << " uses its ability: " << ability->getDescription() << std::endl;
        return;
    } 
    std::cout << getName() << " has no ability." << std::endl;
}

Ability* Minion::getAbility() const {
    return ability;
}

Enchantment* Minion::topEnchantment() {
    if (!enchantments.empty()) {
        return enchantments.back();
    }
    return nullptr;
}

std::unique_ptr<Card> Minion::clone() const {
    return std::make_unique<Minion>(*this);
}

int Minion::getAttack() const { return attack; }
int Minion::getDefense() const { return defense; }
int Minion::getActions() const { return actions; }
void Minion::setActions(int a) { actions = a; }
