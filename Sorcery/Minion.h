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
    Minion(int cost, int attack, int defense);

    void attackTarget(Minion* targetEntity);
    void trigger(std::string eventString);
    void play() override;
    Enchantment* topEnchantment();

    int getAttack() const;
    int getDefense() const;
    int getActions() const;
    void setActions(int a);
};
