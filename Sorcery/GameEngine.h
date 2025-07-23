#ifndef GAMEENGINE
#define GAMEENGINE
#include <vector>
#include <string>
#include "Player.h"
#include "Card.h"
#include "CommandParser.h"
#include "Observer.h"

class Player;
class TextView;
class Card;
class Minion;

class GameEngine {
    std::vector<Player*> players;
    int activePlayer;
    bool testingMode;
    bool graphicMode;
    std::string initFile;
    std::vector<Card*> cardMasterList;
    std::vector<Card*> deckFiles;
    CommandParser parserCmd;

    std::vector<Observer*> observers;
    TextView* textView;


public:
    void run();
    void processCommand(std::string cmdString);
    void registerObserver(Observer*);
    void notifyObservers();

    Player* getPlayer(int idx) const;
    Player* getActivePlayer() const;
    bool isTestingMode() const;

    // Observer methods
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
};

#endif
