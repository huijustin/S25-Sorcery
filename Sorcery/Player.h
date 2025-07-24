#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "GameEngine.h"
#include "Deck.h"
#include "Hand.h"
#include "Board.h"
#include "Graveyard.h"
#include "Ritual.h"
#include "Minion.h"
#include "Card.h"

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

public:
    // ctor
    Player(const std::string &name, const std::string& deckFile, GameEngine* game);
    ~Player();
    // public methods
    void startTurn();
    void endTurn();
    void playCard(int idx);
    void attack(int fromIdx, int toIdx);
    void useAbility(int fromIdx, int targetIdx);
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

};

#endif
