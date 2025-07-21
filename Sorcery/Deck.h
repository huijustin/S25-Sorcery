#pragma once
#include <vector>
#include "Card.h"

class Deck {
    std::vector<Card*> hand;
public:
    void load_deck(const std::string& filename);
    Card* draw();
    void shuffle();
};
