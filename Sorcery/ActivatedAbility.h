#pragma once
#include "Effect.h"
#include "Ability.h"
#include <memory>
#include <string>

class ActivatedAbility : public Ability {
    int cost;

public:
    ActivatedAbility(int cost, std::string description, std::unique_ptr<Effect> effect);

    void useEffect(Minion* target = nullptr) override;
    int getActivationCost() const;
};
