#include "Graveyard.h"

void Graveyard::addMinion(Minion *minion) {
    if (!minion) {
        std::cerr << "Cannot add a null minion to graveyard." << std::endl;
        return;
    } else { 
        minions.emplace_back(minion);
    }
}

Minion* Graveyard::getTop() const {
    if (minions.empty()) {
        std::cerr << "Graveyard is empty, no top minion." << std::endl;
        return nullptr;
    }
    else return minions.back();
}

Minion* Graveyard::resurrectTop() {
    if (minions.empty()) {
        std::cerr << "Graveyard is empty, cannot resurrect minion." << std::endl;
        return nullptr;
    }
    Minion* resurrect = minions.back();
    minions.pop_back();
    return resurrect;
}

bool Graveyard::isEmpty() const {
    return minions.empty();
}
