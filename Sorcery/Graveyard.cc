#include "Graveyard.h"

void Graveyard::addMinion(Minion *minion) {
    if (minion) minions.emplace_back(minion);
}

Minion* Graveyard::getTop() const {
    if (minions.empty()) return nullptr;
    else return minions.back();
}

Minion* Graveyard::resurrectTop() {
    if (minions.empty()) return nullptr;
    Minion* resurrect = minions.back();
    minions.pop_back();
    return resurrect;
}

bool Graveyard::isEmpty() const {
    return minions.empty();
}
