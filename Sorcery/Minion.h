#pragma once
#include "Card.h"
#include "Enchantment.h"
#include <vector>

class Minion : public Card {
    std::vector<Enchantment*> enchantments;
public:
    void attack(Minion* targetEntity);
    void trigger(std::string eventString);
    void play() override;
    int getCost() override;
    Enchantment* topEnchantment();
};
