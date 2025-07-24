#include <GameEngine.h>
#include <TextView.h>
#include <iostream> 
#include <fstream>
#include <sstream>

void GameEngine::run() {
    activePlayer = 0;
    getActivePlayer()->startTurn();
    notifyObservers();

    std::string cmdstring;
    while (!gameOver && std::getline(std::cin, cmdstring)) {
        if (!cmdstring.empty()) {
            this->processCommand(cmdstring);
        }
    }
    // DO WE NEED TO CHECK IF GAME HAS ENDED
    std::cout << "Game has ended.\n";
}

void GameEngine::processCommand(const std::string &input) {
    std::istringstream iss(input);
    std::string cmd;
    std::vector<std::string> args;

    iss >> cmd;
    std::string arg;
    while(iss >> arg) {
        args.push_back(arg);
    }

    //Command cmd = parserCmd.parse(cmdString);

    if (cmd == "help") {
        displayHelp();
    }
    else if (cmd == "end") {
        endTurn();  //NEED TO CHNAGE TO PLAYER ednTurn METHOD
    }
    else if (cmd == "quit") {
        quitGame();
    }
    else if (cmd == "play") {
        if (args.size() == 1) {
            int idx = std::stoi(args[0]);
            getActivePlayer()->playCard(idx);
        }
        else if (args.size() == 3) {
            int idx = std::stoi(args[0]);
            int targetPlayer = std::stoi(args[1]);
            char targetCard = std::stoi(args[2]);
            getActivePlayer()->playCard(idx, getPlayer(targetPlayer), targetCard);  //NEED AN UPDATED playCard IN PLAYER CLASS
        }
        else {
            std::cout << "Invalid number of arguments for attack." << std::endl; //CHECK IF THIS IS THE MESSAGE WE WANT TO USE
        }
    }
    else if (cmd == "attack") {
        if (args.size() == 1) {
            int attackeridx = std::stoi(args[0]);
            getActivePlayer()->attack(attackeridx, getPlayer(1 - activePlayer));
        }
        else if (args.size() == 2) {
            int attackeridx = std::stoi(args[0]);
            int defenderidx = std::stoi(args[1]);
            getActivePlayer()->attack(attackeridx, getPlayer(1 - activePlayer), defenderidx); //AMKE SURE WE HAVE THE RIGHT PARAMETERS IN ATTACK METHOD
        }
        else {
            std::cout << "Invalid number of arguments for attack." << std::endl;
        }
    }
    else if (cmd == "use") {   // Uses Minion Special Ability
        if (args.size() == 1) {
            int minionidx = std::stoi(args[0]);
            getActivePlayer()->useAbility(minionidx); // CHECK IF ONE ARGUMENT IS VALID
        }
        else if (args.size() == 3) {
            int minionidx = std::stoi(args[0]);
            int targetPlayer = std::stoi(args[1]);
            int targetCard = std::stoi(args[2]);
            getActivePlayer()->useAbility(minionidx, getPlayer(targetPlayer), targetCard); // NEED TO CHECK ARGUMENTS
        }
        else {
            std::cout << "Invalid number of arguments for attack." << std::endl; //CHECK IF THIS IS THE MESSAGE WE WANT TO USE
        }
    }
    else if (cmd == "inspect") {       // NHAN TAKING CARE OF THIS CASE
        if (args.size() == 1) {
            int minionidx = std::stoi(args[0]);
            //getActivePlayer()-> // CHECK IF ONE ARGUMENT IS VALID
        }
    }
    else if (cmd == "hand") {
        textView->printHand(activePlayer);
    }
    else if (cmd == "board") {
        textView->printBoard();
    }
    else if (cmd == "draw"  && testingMode) {
        getActivePlayer()->drawCard();
    }
    else if (cmd == "discard" && testingMode) {
        if (args.size() == 1) {
            int idx = std::stoi(args[0]);
            discardCard(idx);
        } 
        else {
            std::cout << "Invalid number of arguments for attack." << std::endl;
        }
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


void GameEngine::quitGame() { // go back to main and main will terminate the program
  gameOver = true;
}


void GameEngine::discardCard(int idx) {
    Card* discardedCard = getActivePlayer()->getHand().removeCard(idx - 1);
    if (!discardedCard) {
        std::cout << "Invalid card index.\n";
        return;
    }
    delete discardedCard;
    std::cout << "Card discarded.\n";
}

void GameEngine::startTurn() {
    getActivePlayer()->startTurn(); // CHECK POINTER
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

Player* GameEngine::getActivePlayer() const {
    if (activePlayer < 0 || activePlayer >= players.size()) {
        std::cerr << "Invalid active player index: " << activePlayer << std::endl;
        return nullptr;
    }
    return players[activePlayer];
}

/*
void GameEngine::attack(int attackeridx, std::optional<int> targetidx) {
    Player* current = players[activerPlayer];
    Player* opponent = players[1 - activePlayer];

    Minion* attacker = current->getMinion(attackeridx);
    if (!attacker) {
        std::cout << "Invalid attacking minion index." << std::endl;
        return;
    }

    if (!attacker->canAttack()) {
        std::cout << "this minion cannot attack right now." << std::endl;
        return;
    }

    if (targetidx.has_value()) {
        Minion* target = opponent->getMinion(targetidx.value());
        if (!target) {
            std:cout << "invalid target minion." << std::endl;
            return;
        }
        attacker->attack(target); // Attacks minion
    }
    else {
        attacker->attack(opponent); // Directly attacks the player
    }
   
    notifyObservers();
}
 */
