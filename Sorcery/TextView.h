#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "GameEngine.h"
#include "ascii_graphics.h"

class Player;
class Card;
class Minion;
class Ritual;
class Enchantment;
#include "Observer.h"
#include <iostream>
#include <vector>

class TextView : public Observer {
    GameEngine* game;

public:
    TextView(GameEngine* game);
    ~TextView();

    // Observer interface
    void notify() override;

    // Print the game board
    void printBoard() const;
    // Print player hand
    void printHand(int playerIdx) const;
    // Inspect a minion
    void inspectMinion(int playerIdx, int minionIdx) const;
};

#endif
