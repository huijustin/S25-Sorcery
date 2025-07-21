#pragma once
#include "Ability.h"
#include "Minion.h"

class BuffAbility : public Ability {
public:
    void useEffect(Minion* targetEntity);
};