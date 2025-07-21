#pragma once
#include "Card.h"

class Spell : public Card {
public:
    void activate();
    void play() override;
    int getCost() override;
};