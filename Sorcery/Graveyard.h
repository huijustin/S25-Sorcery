#pragma once
#include <vector>
#include "Minion.h"

class Graveyard {
    std::vector<Minion*> minions;
public:
    void addMinion(Minion*);
    Minion* top();
};
