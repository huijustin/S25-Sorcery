#include <GameEngine.h>
#include <TextView.h>
#include <iostream> 
#include <fstream>
#include <sstream>

void GameEngine::run() { // Check if we need GameEngiene Method
    activePlayer = 0;
    players[activePlayer]->startTurn();
    notifyObservers();

    std::string cmdstring;
    while (!gameOver && std::getline(std::cin, cmdstring)) {
        if (!cmdstring.empty()) {
            processCommand(cmdstring);
        }
    }
    std::cout << "Game has ended.\n";
}

void processCommand(std::string cmdString) {
    Command cmd = parserCmd.parse(cmdString);

    if (cmd.type == "help") {
        displayHelp();
    }
    else if (cmd.type == "end") {
        endTurn();
    }
    else if (cmd.type == "quit") {
        quitGame();
    }
    else if (cmd.type == "play") {
        Player.playCard(idx);  // CHECK WITH GROUP
    }
    else if (cmd.type == "attack") {
       attack(); // CHECK WITH GROUP
    }
    else if (cmd.type == "use") {
        useMinion(); // CHECK WITH GROUP
    }
    else if (cmd.type == "inspect") {
        inspectMinion(); // CHECK WITH GROUP
    }
    else if (cmd.type == "hand") {
        printHand(); // CHECK WITH GROUP
    }
    else if (cmd.type == "board") {
        printBoard(); // CHECK WITH GROUP
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

Player* GameEngine::getInactivePlayer() const {
    int inactiveIdx = (activePlayer + 1) % players.size();
    return getPlayer(inactiveIdx);
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

void GameEngine::displayHelp() {
    std::cout << " Commands:\n"
    << " help -- Display this message.\n"
    << "end -- End the current player’s turn.\n"
    << "quit -- End the game.\n"
    << "attack minion other-minion -- Orders minion to attack other-minion.\n"
    << "attack minion -- Orders minion to attack the opponent.\n"
    << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n"
    << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player.\n"
    << "inspect minion -- View a minion’s card and all enchantments on that minion.\n"
    << "hand -- Describe all cards in your hand.\n"
    << "board -- Describe all cards on the board.\n"
    << std::endl; 
}

void GameEngine::endTurn() { // Make it so there is a Player 1 and Player 2 basis
    players[activePlayer]->endTurn();
    if (activePlayer == 1) {
        activePlayer = 0;
    }
    else {
        activePlayer = 1;
    }
    players[activePlayer]->startTurn();
} 

void GameEngine::quitGame() { // go back to main and main will terminate the program
  gameOver = true;
}

void GameEngine::discardCard(int idx) {
    if (idx <0 || idx >= currentPlayer->getHand().size()) {
        std::cout << "invalid card inde.\n";
        return;
    }

    currentPlayer->discardCard(idx);
    std::cout << "Card Discarded.\n";
}

void GameEngine::attack(int attackeridx, std::optional<int> targetidx) {
    Player* current = players[activerPlayer];
    Player* opponent = players[1 - activePlayer];

    Minion* attacker = current->getMinion(attackeridx);
    if (!attacker) {
        std::cout << "Invalid attacking minion index." << std::endl;
        
    }
}
