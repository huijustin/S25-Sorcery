#pragma once
#include "Ritual.h"
#include "Player.h"

class DarkRitual : public Ritual {
public:
    DarkRitual();
    std::unique_ptr<Card> clone() const override;
    void trigger(const std::string& triggerString, Player* player) override;
};
