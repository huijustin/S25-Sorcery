#ifndef CARD_H
#define CARD_H
#include <string>

class GameEngine;
class Player;

class Card {
    std::string name;
    int cost;
  public:
    virtual ~Card() = default;
    virtual void play(GameEngine &engine, Player &player) = 0;

    virtual int getCost() const = 0;
    virtual std::string getname() const = 0;
}

#endif
