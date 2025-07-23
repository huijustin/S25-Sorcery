#include <GameEngine.h>
#include <iostream>  // CHeck if incldues shoudl go in .h or stay in .cc
#include <fstream>
#include <sstream>

GameEngine::run() { // Check if we need GameEngiene Method
    std::cout << "starting Game Engine " << std::endl;  // CHECK STD::

   activePlayer = 0;    //Initializes the active Player

   initializeGame();    // Initializes players

   if (!initFile.empty()) {
    loadInitializationFile();
   }

   gameLoop;    // Main game loop

   std::cout << "Game ended." < std::endl;  // CHECK STD::
}

void processCommand(std::string cmdString) {
    Command cmd = parserCmd.parse(cmdString);

    if (cmd.type == "help") {
        displayHelp();  // WHAT IS THE HELP MESSAGE
    }
    else if (cmd.type == "end") {
        endTurn();
    }
    else if (cmd.type == "quit") {
        quitGame();
    }
    else if (cmd.type == "play") {
        playCard();  // CHECK WITH GROUP
    }
    else if (cmd.type == "attack") {
        attackMinion(); // CHECK WITH GROUP
    }
    else if (cmd.type == "use") {
        useMinion(); // CHECK WITH GROUP
    }
    else if (cmd.type == "inspect") {
        inspectMinion(); // CHECK WITH GROUP
    }
    else if (cmd.type == "hand") {
        displayHand(); // CHECK WITH GROUP
    }
    else if (cmd.type == "board") {
        displayBoard(); // CHECK WITH GROUP
    }
    else if (cmd.type == "draw"  && testingMode) {
        inspectMinion(); // CHECK WITH GROUP
    }
    else if (cmd.type == "discard" && testingMode) {
       discardCard(); // CHECK WITH GROUP
    }
    else {
        std::cout << "Invalid command" << std::endl;
    }
    notifyObservers();
}

Player* GameEngine::getPlayer(int idx) const {
    if (idx < 0 || idx >= players.size()) {
        std::cerr << "Invalid player index: " << idx << std::endl;
        return nullptr;
    }
    return players[idx];
}

Player* getActivePlayer() const {
    if (activePlayer < 0 || activePlayer >= players.size()) {
        std::cerr << "Invalid active player index: " << activePlayer << std::endl;
        return nullptr;
    }
    return players[activePlayer];
}

bool GameEngine::isTestingMode() const {
    return testingMode;
}

void GameEngine::attach(Observer* o) {
    observers.push_back(o);
}

void GameEngine::detach(Observer* o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            return;
        }
    }
}

void GameEngine::notifyObservers() {
    for (auto observer : observers) {
        observer->notify();
    }
}
