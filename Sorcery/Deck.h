#pragma once
#include <vector>
#include "Card.h"

class Deck {
    std::vector<Card*> hand;
public:
    Card* draw();
    void shuffle();
};