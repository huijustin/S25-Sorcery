#pragma once
#include <vector>
#include "Minion.h"

class Board {
public:
    void addMinion(Player* p, Minion* m);
    void removeMinion(Player* p, int idx);
};