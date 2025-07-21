#pragma once
#include "Ability.h"

class ActivateAbility : public Ability {
public:
    void useEffect() override;
    int getCost();
};