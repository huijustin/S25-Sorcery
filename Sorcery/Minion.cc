#include "Minion.h"
#include "Effect.h"
#include "DamageEffect.h"
#include "SummonEffect.h"
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

    useActions(1);
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

void Minion::useAbility(Minion* target, Board* board) {
    if (actions <= 0) { return; }

    // Check for no Ability
    if (!getAbility()) {
        std::cout << getName() << " has no ability." << std::endl;
        return;
    }
    Effect* effect = getAbility()->getEffect();
    // Check for no effect
    if (!effect) {
        std::cerr << "Error: Ability has no effect." << std::endl;
        return;
    }

    // SummonEffect requires board
    if (auto* summon = dynamic_cast<SummonEffect*>(effect)) {
        if (!board) {
            std::cerr << getName() << "'s summon ability requires a board but none was provided." << std::endl;
            return;
        }

        summon->setBoard(board);
        getAbility()->useEffect();  // Summoned minion is specified on creation of effect
    }
    
    // If the effect requires a minion target
    else if (effect->supportsTarget()) {
        if (!target) {
            std::cerr << getName() << "'s ability needs a target, but none was provided." << std::endl;
            return;
        }

        effect->setTarget(target);
        getAbility()->useEffect(target);
    }

    // If no target needed
    else {
        getAbility()->useEffect();
    }
    useActions(1);
    std::cout << getName() << " uses its ability: " << ability->getDescription() << std::endl;
}

Ability* Minion::getAbility() const {
    return ability;
}

Minion* Minion::top() {
    return this;
}

void Minion::roundStart() {
    if (getActions() <= 0) { setActions(1); }
}

std::unique_ptr<Card> Minion::clone() const {
    return std::make_unique<Minion>(*this);
}

int Minion::getAttack() const { return attack; }
int Minion::getDefense() const { return defense; }
int Minion::getActions() const { return actions; }
void Minion::setActions(int a) { actions = a; }
void Minion::useActions(int a) { if (actions >= a ) { actions -= a; }}
