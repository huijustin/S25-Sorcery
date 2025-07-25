#include "Board.h"
#include "Minion.h"
#include <iostream>

Board::~Board() { for (auto m : minions) delete m; }

bool Board::addMinion(Minion* m) {
    if (minions.size() >= MAX_MINIONS) {
        std::cerr << "Board is full, cannot add minion." << std::endl; 
        return false;  
    }
    if (!m) {
        std::cerr << "Cannot add a null minion to board" << std::endl;
        return false;
    }
    minions.emplace_back(m);
    return true;
}

Minion* Board::removeMinion(int idx) {
    if (idx < 1 || static_cast<std::size_t>(idx) > minions.size()) {
        std::cerr << "Invalid index for removing minion: " << idx << " in Board" << std::endl;
        return nullptr;
    }
    Minion* removed = minions[idx - 1];
    minions.erase(minions.begin() + (idx - 1));
    return removed;
}

void Board::resetActions() {
    for (auto& minion : minions) {
        if (minion) {
            minion->roundStart(); // Reset actions for each minion
        }
    }
}

const std::vector<Minion*>& Board::getMinions() const { return minions; }

void Board::replaceMinion(int idx, Minion* newMinion) {
    if (idx < 1 || static_cast<std::size_t>(idx) > minions.size()) {
        std::cerr << "Invalid index for replacing minion: " << idx << std::endl;
        return;
    }
    delete minions[idx - 1]; // prevent memory leak
    minions[idx - 1] = newMinion;
}
