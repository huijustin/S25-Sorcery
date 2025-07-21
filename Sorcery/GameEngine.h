#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Card.h"
#include "CommandParser.h"
#include "Observer.h"

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

public:
    void run();
    void processCommand(std::string cmdString);
    void registerObserver(Observer*);
    void notifyObservers();
};