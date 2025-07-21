#pragma once
#include "Card.h"

class Enchantment : public Card {
public:
    virtual void apply() = 0;
};