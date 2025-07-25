#include "GameEngine.h"
#include "CardFactory.h"
#include "TextView.h"
#include "GraphicsView.h"
#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include "Deck.h"
#include "Hand.h"

extern CardFactory Factory;

GameEngine::GameEngine(bool testingMode, bool graphicMode, std::string initFile, std::string deck1File, std::string deck2File) :
    testingMode{testingMode}, graphicMode{graphicMode}, initFile{initFile}, activePlayer{0}, gameOver{false} {  // Constructor

        std::string player1DeckFile;
        if (deck1File.empty()) {
            player1DeckFile = "default.deck";
        }
        else {
            player1DeckFile = deck1File;
        }

        std::string player2DeckFile;
        if (deck2File.empty()) {
            player2DeckFile = "default.deck";
        }
        else {
            player2DeckFile = deck2File;
        }

        Deck* deck1 = new Deck();
        try {
            deck1->load_deck(player1DeckFile, Factory);
        }
        catch (const std::exception& e) {
            delete deck1;
            throw std::runtime_error("Failed to load deck for Player 1");
        }

        Deck* deck2 = new Deck();
        try {
            deck2->load_deck(player2DeckFile, Factory);
        }
        catch (const std::exception& e) {
            delete deck2;
            throw std::runtime_error("Failed to load deck for Player 2");
        }

        std::string name1, name2;
        if (initFile == "") {
            std::cout << "Enter Player 1's name: ";
            std::cin >> name1;
            std::cout << "Enter Player 2's name: ";
            std::cin >> name2;
            playerNames.push_back(name1);
            playerNames.push_back(name2);
        }
        else {
            std::string line;
            int count = 0;
            std::ifstream file(initFile);
            while (std::getline(file, line)) {
                if (count == 0) {
                    std::cout << "count is: " << count << std::endl;
                    name1 = line;
                    playerNames.push_back(name1);
                    count++;
                }
                else if (count == 1) {
                    std::cout << "thecount is: " << count << std::endl;
                    name2 = line;
                    playerNames.push_back(name2);
                    count++;
                }
                else {
                    std::cout << "the count is: " << count << std::endl;
                    processCommand(&line);
                    std::cout << "doesn't get here: " << count << std::endl;
                    count++;
                }
            }
            if (count == 1) {
                std::cout << "Enter Player 2's name: ";
                std::cin >> name2;
                playerNames.push_back(name2);
            }
        }
        players.emplace_back(new Player(name1, deck1, this));
        players.emplace_back(new Player(name2, deck2, this));

        textView = new TextView{this};
        if (graphicMode) {
            graphicsView = new GraphicsView{this};
        }
    }

GameEngine::~GameEngine() { // Destructor
    delete textView;
    delete graphicsView;
    for (auto *player : players) {
        delete player;
    }
}


void GameEngine::run() {
    activePlayer = 0;
    getActivePlayer()->startTurn();
    std::cout << "It is now " << playerNames[activePlayer] << "'s turn" << std::endl;
    notifyObservers();

    std::string cmdstring;
    while (!gameOver && std::getline(std::cin, cmdstring)) {
        if (!cmdstring.empty()) {
            this->processCommand(cmdstring);
        }
    }
    std::cout << "Game has ended.\n"; // Game ended message
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

    if (cmd == "help") {
        displayHelp(); // call to displayHelp()
    }
    else if (cmd == "end") {
        endTurn();  // call to endTurn()
    }
    else if (cmd == "quit") {
        quitGame(); // call to quitGame()
    }
    else if (cmd == "play") {
        if (args.size() == 1) { // Checks the amount of arguments
            int idx = std::stoi(args[0]);
            getActivePlayer()->playCard(idx);
        }
        else if (args.size() == 3) {
            int idx = std::stoi(args[0]);
            int targetPlayer = std::stoi(args[1]);
            char targetCard = std::stoi(args[2]);
            getActivePlayer()->playCard(idx, getPlayer(targetPlayer-1), targetCard); 
        }
        else {
            std::cout << "Invalid number of arguments for attack." << std::endl; // Message for invalid number of arguments
        }
    }
    else if (cmd == "attack") {
        if (args.size() == 1) {     // Checks the amount of arguments
            int attackeridx = std::stoi(args[0]);
            getActivePlayer()->attack(attackeridx);
        }
        else if (args.size() == 2) {
            int attackeridx = std::stoi(args[0]);
            int defenderidx = std::stoi(args[1]);
            getActivePlayer()->attack(attackeridx, defenderidx);
        }
        else {
            std::cout << "Invalid number of arguments for attack." << std::endl; // Message for invalid number of arguments
        }
    }
    else if (cmd == "use") {   // Uses Minion Special Ability
        if (args.size() == 1) {
            int minionidx = std::stoi(args[0]);
            getActivePlayer()->useAbility(minionidx);
        }
        else if (args.size() == 3) {
            int minionidx = std::stoi(args[0]);
            int targetPlayer = std::stoi(args[1]);
            int targetCard = std::stoi(args[2]);
            getActivePlayer()->useAbility(minionidx, getPlayer(targetPlayer-1), targetCard);
        }
        else {
            std::cout << "Invalid number of arguments for attack." << std::endl; // Message for invalid number of arguments
        }
    }
    else if (cmd == "inspect") {  
        int minionidx = std::stoi(args[0]);
        textView->inspectMinion(activePlayer, minionidx);
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

Player* GameEngine::getActivePlayer() const {
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
    std::cout << "Commands:\n"
    << " help -- Display this message.\n"
    << " end -- End the current player’s turn.\n"
    << " quit -- End the game.\n"
    << " attack minion other-minion -- Orders minion to attack other-minion.\n"
    << " attack minion -- Orders minion to attack the opponent.\n"
    << " play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n"
    << " use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player.\n"
    << " inspect minion -- View a minion’s card and all enchantments on that minion.\n"
    << " hand -- Describe all cards in your hand.\n"
    << " board -- Describe all cards on the board.\n"
    << std::endl; 
}


void GameEngine::quitGame() { // go back to main and main will terminate the program
  gameOver = true;
}


void GameEngine::discardCard(int idx) {
    Card* discardedCard = getActivePlayer()->getHand()->removeCard(idx - 1);
    if (!discardedCard) {
        std::cout << "Invalid card index.\n";
        return;
    }
    delete discardedCard;
    std::cout << "Card discarded.\n";
}

void GameEngine::startTurn() {
    getActivePlayer()->startTurn();
}

void GameEngine::endTurn() { 
    if (activePlayer == 1) {    // Makes the other player the active one
        activePlayer = 0;
    }
    else {
        activePlayer = 1;
    }
    std::cout << "It is now " << playerNames[activePlayer] << "'s turn" << std::endl;
    players[activePlayer]->startTurn();
} 
