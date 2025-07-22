#pragma once
#include "Card.h"

class Spell : public Card {
public:
    Spell(int cost);
    void activate();
    void play() override;
};
