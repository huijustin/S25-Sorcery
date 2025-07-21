#pragma once
#include "Ability.h"
#include "Minion.h"

class DamageAbility : public Ability {
public:
    void useEffect(Minion* targetEntity);
};
