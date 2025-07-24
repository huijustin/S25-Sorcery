#include "Minion.h"
#include "Effect.h"
#include "DamageEffect.h"
#include "SummonEffect.h"
#include "ActivatedAbility.h"
#include "ascii_graphics.h"
#include <iostream>

Minion::Minion(int ID, std::string name, int cost, int attack, int defence, std::unique_ptr<Ability> ability, std::string cardText)
    : Card(ID, std::move(name), cost, std::move(cardText)), // Card attributes
      attack(attack), defence(defence), actions(0), ability(std::move(ability)) {} // Minion attributes

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
    defence -= dmg;

    if (defence <= 0) {
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
    return ability.get();
}

Minion* Minion::top() {
    return this;
}

void Minion::roundStart() {
    if (getActions() <= 0) { setActions(1); }
}

void Minion::roundEnd() {
    
}

// Keep track of enchantments
std::vector<Card*> Minion::getEnchantmentStack() const {
    std::vector<Card*> stack;
    for (const auto& enchantment : enchantmentStack) {
        stack.push_back(enchantment.get());
    }
    return stack;
}
void Minion::addEnchantmentCard(std::unique_ptr<Card> spellCard) { enchantmentStack.emplace_back(std::move(spellCard)); }

std::unique_ptr<Card> Minion::clone() const {
    return std::make_unique<Minion>(cardID, name, cost, attack, defence,ability ? ability->clone() : nullptr,cardText);}

int Minion::getAttack() const { return attack; }
int Minion::getDefence() const { return defence; }
int Minion::getActions() const { return actions; }
void Minion::setActions(int a) { actions = a; }
void Minion::useActions(int a) { if (actions >= a ) { actions -= a; }}

std::unique_ptr<Minion> Minion::cloneMinion() const {
    return std::make_unique<Minion>(cardID,name,cost,attack,defence,ability ? ability->clone() : nullptr,cardText);
}

card_template_t Minion::getTemplate() const {
    // check if minion has no ability
    if (!ability) {
        return display_minion_no_ability(name, cost, attack, defense);
    } 

    // check if minion has activated ability
    if (auto *act = dynamic_cast<ActivatedAbility*>(ability)) {
        return display_minion_activated_ability(
            name, cost, attack, defense, act->getActivationCost(), act->getDescription());
    }
    // else it has a triggered ability
    return display_minion_triggered_ability(
        name, cost, attack, defense, ability->getDescription());
}
