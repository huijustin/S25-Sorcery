#ifndef GAMEENGINE
#define GAMEENGINE
#include <vector>
#include <string>
#include "Observer.h"

class Player;
class TextView;
class Card;
class Minion;
class GraphicsView;

class GameEngine {
    std::vector<Player*> players;
    int activePlayer;
    bool testingMode;
    bool graphicMode;
    bool gameOver;
    std::string initFile;
    std::vector<Card*> cardMasterList;
    std::vector<Card*> deckFiles;
    std::vector<std::string> playerNames;
    std::string deck1File = "";
    std::string deck2File = "";
    

    std::vector<Observer*> observers;
    TextView* textView = nullptr;
    GraphicsView* graphicsView = nullptr;

    void displayHelp();
    void startTurn();
    void endTurn();
    void quitGame();
    void playCard(int idx);
    void attack();
    void discardCard(int idx);
    // Make 2 plays, deck, card factory
public:
    GameEngine(bool testingMode, bool graphicMode, std::string initFile = "", std::string deck1File = "", std::string deck2File = "");


    void run();
    void processCommand(const std::string &input);
    void registerObserver(Observer*);

    Player* getPlayer(int idx) const;
    Player* getActivePlayer() const;
    Player* getInactivePlayer() const;
    bool isTestingMode() const;

    // Observer methods
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
};

#endif
