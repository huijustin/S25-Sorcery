#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "hand.h"
#include <string>

class Player {
    std::string name;
    int life;
    int magic;
    Deck deck;
    Hand hand;
  public:
    Player(const std::string &name);

    // draw a card from deck and add it to hand, false otherwise
    bool drawCard();
    void startTurn();
    void endTurn();

    // accessors / setters
    std::string getName() const;
    int getLife() const;
    void setLife(int life);
    int getMagic() const;
    void setMagic(int magic);

}

#endif
