#pragma once
#include "Ability.h"
#include "Effect.h"
#include <memory>
#include <string>

class ActivatedAbility : public Ability {
    int cost;
    std::string description;
    std::unique_ptr<Effect> effect;

public:
    ActivatedAbility(int cost, std::string description, std::unique_ptr<Effect> effect);

    void useEffect(Minion* target = nullptr) override;
    std::string getDescription() const override;
    int getActivationCost() const;
};
