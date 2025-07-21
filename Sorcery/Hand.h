#pragma once
#include <vector>
#include "Card.h"

class Hand {
    std::vector<Card*> hand;
public:
    void addCard(Card*);
    Card* removeCard(int index);
};
