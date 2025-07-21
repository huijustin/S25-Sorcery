#pragma once
#include <string>
#include "Deck.h"
#include "Board.h"
#include "Hand.h"
#include "Graveyard.h"
#include "Ritual.h"

class Player {
    std::string name;
    int life;
    int magic;
    Deck deck;
    Hand hand;
    Board board;
    Graveyard graveyard;
    Ritual ritual;

public:
    void playCard(int index);
    void attack(int fromIdx, int toIdx);
    void useAbility(int fromIdx, int toIdx);
};