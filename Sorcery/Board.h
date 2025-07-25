#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Minion;

class Board {
    std::vector<Minion*> minions;
    static const int MAX_MINIONS = 5;
public:
    ~Board();
    // adds a minion to board, false if board is full
    bool addMinion(Minion* m);
    Minion* removeMinion(int idx);
    void resetActions();
    
    // accessors
    const std::vector<Minion*>& getMinions() const;
};

#endif
