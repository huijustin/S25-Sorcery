#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Deck.h"
#include "Hand.h"
#include "Board.h"
#include "Graveyard.h"
#include "Ritual.h"
#include "Minion.h"
#include "Card.h"
#include "GameEngine.h"
#include "ActivatedAbility.h"
#include "SummonEffect.h"
#include "Enchantment.h"

class GameEngine;

class Player {
    std::string name;
    int life;
    int magic;
    Deck deck;
    Hand hand;
    Board board;
    Graveyard graveyard;
    Ritual* ritual;
    GameEngine* game;

public:
    // ctor
    Player(const std::string &name, const std::string& deckFile, GameEngine* game);
    ~Player();


    // accessors / setters
    std::string getName() const;
    int getLife() const;
    int getMagic() const;
    Graveyard* getGraveyard() const;
    Ritual* getRitual() const;
    Board& getBoard() const;
    Hand& getHand() const;

    // for testing
    void setLife(int l);
    void setMagic(int m);

    // game actions
    void takeDamage(int amount);
    void gainMagic(int amount);
    void spendMagic(int cost);

    // Player actions
    void playCard(int idx);
    void playCard(int idx, Player* target, char cardType);
    void attack(int idx);
    void attack(int fromIdx, int toIdx);
    void useAbility(int idx);
    void useAbility(int idx, Player* target, char cardType);
    void drawCard();
};

#endif
