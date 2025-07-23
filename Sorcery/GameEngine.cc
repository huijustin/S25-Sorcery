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



void registerObserver(Observer* observer) {
    if (observer != nullptr) {
        observers.push_back(observer)
        std::cout << "Observer registered succesfully." << std::endl;
    }
}
void notifyObservers();
