#pragma once
#include "Card.h"

class Ritual : public Card {
public:
    void trigger(std::string eventString);
    void play() override;
    int getCost() override;
    int getCharges();
};