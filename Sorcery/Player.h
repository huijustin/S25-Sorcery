#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <memory>


class GameEngine;
class Deck;
class Hand;
class Board;
class Graveyard;
class Ritual;
class Minion;
class Card;

class Player {
    std::string name;
    int life;
    int magic;
    Deck* deck;
    Hand* hand;
    Board* board;
    Graveyard* graveyard;
    std::unique_ptr<Ritual> ritual;
    GameEngine* game;
    bool firsTurn;

public:
    // ctor
    Player(const std::string &name, Deck* deck, GameEngine* game);
    ~Player();
    // public methods
    void startTurn();
    void endTurn();
    void playCard(int idx);
    void playCard(int idx, Player* target, int cardIdx);
    void attack(int idx);
    void attack(int fromIdx, int toIdx);
    void useAbility(int idx);
    void useAbility(int fromIdx, int targetIdx);
    void useAbility(int idx, Player* target, int cardIdx);
    void drawCard();

    // accessors / setters
    std::string getName() const;
    int getLife() const;
    int getMagic() const;
    const Graveyard* getGraveyard() const;
    Ritual* getRitual() const;
    Board* getBoard() const;
    Hand* getHand() const;

    // for testing
    void setLife(int l);
    void setMagic(int m);

    // game actions
    void takeDamage(int amount);
    void gainMagic(int amount);
    void spendMagic(int cost);
    void setRitual(std::unique_ptr<Ritual> newRitual);
    void cleanupDeadMinions();

};

#endif
