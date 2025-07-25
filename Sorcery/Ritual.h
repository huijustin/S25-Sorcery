#ifndef RITUAL
#define RITUAL

#include "Card.h"
#include <string>
#include "ascii_graphics.h"

class Player;

class Ritual : public Card {
protected:
    int activationCost;
    int charges;
    std::string triggerCondition;

public:
    Ritual(int id, std::string name, int cost, std::string cardText, int activationCost, int charges, std::string triggerCondition);

    virtual void trigger(const std::string& eventString, Player* player) = 0;
    void play() override;
    void play(Player* owner);

    int getCost() override;
    int getCharges() const;
    std::string getTriggerCondition() const;

    std::unique_ptr<Card> clone() const override;

    virtual card_template_t getTemplate() const;
};

#endif
