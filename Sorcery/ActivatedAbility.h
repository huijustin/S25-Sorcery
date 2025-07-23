#pragma once
#include "Ability.h"
#include "Effect.h"
#include <string>

class ActivatedAbility : public Ability {
    int cost;
    std::string description;
    Effect* effect;

public:
    ActivatedAbility(int cost, std::string description, Effect* effect);
    void useEffect() override;
    std::string getDescription() const override;
    int getActivationCost() const;
};
