#ifndef GRAVEYARD_H
#define GRAVEYARD_H
#include <vector>
#include "Minion.h"

class Graveyard {
    std::vector<Minion*> minions;
public:
    ~Graveyard();
    // adds minion to top of graveyard
    void addMinion(Minion* minion);
    // returns top minion, nullptr if empty
    Minion* getTop() const;
    // removes and return top minion in graveyard
    Minion* resurrectTop();
    // returns true if graveyard is empty, else false
    bool isEmpty() const;
};

#endif
