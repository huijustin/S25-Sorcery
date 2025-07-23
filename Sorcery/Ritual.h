#ifndef RITUAL
#define RITUAL
#include "Card.h"

class Ritual : public Card {
private:
    int activationCost;
    int charges;
    std::string triggerCondition;

public:
    void trigger(std::string eventString);
    void play() override;
    int getCost() override;
    int getCharges();
};

#endif

