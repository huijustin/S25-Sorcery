#pragma once
#include "Card.h"
#include "Enchantment.h"
#include <vector>

class Minion : public Card {
protected:
    int attack;
    int defense;
    int actions;
    std::vector<Enchantment*> enchantments;

public:
    Minion(int ID, std::string name, int cost, int attack, int defense);

    void attackTarget(Minion* targetEntity);

    // Minions can take damage from multiple sources so create a takeDamage method
    void takeDamage(int dmg); 

    void trigger(const std::string& eventString);
    void play() override;

    int getAttack() const;
    int getDefense() const;
    int getActions() const;
    void setActions(int a);
    Enchantment* topEnchantment();
};