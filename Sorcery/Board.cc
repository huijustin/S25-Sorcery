#include "Board.h"

Board::~Board() { for (auto m : minions) delete m; }

bool Board::addMinion(Minion* m) {
    if (slots.size() >= MAX_MINIONS) return false;
    minions.emplace_back(m);
    return true;
}

Minion* Board::removeMinion(int idx) {
    if (idx < 1 || idx > slots.size()) return nullptr;
    Minion* removed = minions[idx - 1];
    minions.erase(minions.begin() + (idx - 1));
    return removed;
}

const std::vector<Minion*>& Board::getMinions() const { return minions; }
