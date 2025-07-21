#pragma once
#include "Ability.h"

class TriggerAbility : public Ability {
public:
    void useEffect();
    void trigger(std::string eventString);
};