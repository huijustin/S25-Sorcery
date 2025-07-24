#ifndef RITUAL
#define RITUAL

#include "Card.h"
#include <string>

class Player; // Forward declaration

class Ritual : public Card {
private:
    int activationCost;
    int charges;
    std::string triggerCondition;

public:
    Ritual(int id, std::string name, int cost, std::string cardText, int activationCost, int charges, std::string triggerCondition);

    void trigger(std::string eventString);
    void play() override;
    void play(Player* owner);

    int getCost() override;
    int getCharges() const;
    std::string getTriggerCondition() const;

    std::unique_ptr<Card> clone() const override;
};

#endif
