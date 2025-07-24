#include "Player.h"
#include <iostream>

Player::Player(const std::string &name, const std::string& deckFile, GameEngine* game)
    : name{name}, life{20}, magic{3}, ritual{nullptr}, game{game} {
    deck.load_deck(deckFile);
    if (!game) {
        std::cerr << "Error: GameEngine pointer is null." << std::endl;
        throw std::invalid_argument("GameEngine pointer cannot be null");
    }
    if (!game->isTestingMode()) {
        deck.shuffle();
    }
    for (int i = 0; i < 5; ++i) {
        drawCard();
    }
}

Player::~Player() { delete ritual; }

std::string Player::getName() const { return name; }
int Player::getLife() const { return life; }
int Player::getMagic() const { return magic; }
Ritual* Player::getRitual() const { return ritual; }
Graveyard* Player::getGraveyard() const { return &graveyard; }
Board& Player::getBoard() const { return board; }
Hand& Player::getHand() const { return hand; }

// for testing
void Player::setLife(int l) { life = l; }
void Player::setMagic(int m) { magic = m; }

void Player::takeDamage(int amount) { life -= amount; }
void Player::gainMagic(int amount) { magic += amount; }
void Player::spendMagic(int cost) { magic -= cost; }


void Player::startTurn() {
    gainMagic(1);
    drawCard();
    // TODO: trigger "start of turn" effects (rituals, triggers)
}

void Player::endTurn() {
    // TODO: trigger any “end of turn” ritual or minion triggers
}

void Player::playCard(int idx) {
    if (idx < 1 || idx > hand.getSize()) {
        std::cerr << "Error: Invalid card index." << std::endl;
        return;
    }
    Card *c = hand.getCard(idx);
    if (!c) {
        std::cerr << "Error: Invalid card index or Hand is empty" << std::endl;
        return;
    }
    if (c->getCost() > magic) {
        std::cerr << "Error: Not enough magic to play this card." << std::endl;
        return;
    }
    // attempt to play the card
    bool playSuccessful = false;

    // Check if the card is a Ritual
    if (Ritual* ritualCard = dynamic_cast<Ritual*>(c)) {
        if (this->ritual) {
            std::cerr << "Error: Ritual slot is already occupied." << std::endl;
            return;
        }
        this->ritual = ritualCard; 
        Card *toPlay = hand.removeCard(idx); 
        playSuccessful = true;
    }

    // Check if the card is a Minion
     else if (Minion* minionCard = dynamic_cast<Minion*>(c)) {
        if (board.addMinion(minionCard)) {
            Card *toPlay = hand.removeCard(idx); 
            playSuccessful = true;
        } else {
            std::cerr << "Error: Board is full, cannot add minion." << std::endl;
            return;
        }
    }

    // TODO: Handle other card types (Spells, Enchantments, etc.)

    if (playSuccessful) {
        spendMagic(c->getCost());
        c->play();
    }
}

void Player::attack(int fromIdx, int toIdx) {
    if (fromIdx < 1 || fromIdx > board.getMinions().size()) {
        std::cerr << "Error: Invalid attacker Index" << std::endl;
        return;
    }
    Minion* attacker = board.getMinions()[fromIdx - 1];
    if (toIdx == 0) {
        // attack opposing player
        // TODO: implement in GameEngine context
    } else {
        // attack opposing minon
        // TODO: look up opposing player's board and resolve combat
    }
}

void Player::useAbility(int fromIdx, int targetIdx) {
    if (fromIdx < 1 || fromIdx > board.getMinions().size()) {
        std::cerr << "Error: Invalid attacking minion index" << std::endl;
        return;
    }
    Minion* m = board.getMinions()[fromIdx - 1];
    // Todo: implement m->activateAbility(target)

    if (minion->getAbility()->getEffect()->supportsTarget()) {
        // the ability needs a target
        if (targetIdx < 1 || targetIdx > board.getMinions().size()) {
            std::cerr << "Error: Invalid target index" << std::endl;
            return;
        }
        Board opponentBoard = game->getInactivePlayer()->getBoard();
        Minion* targetMinion = opponentBoard.getMinions()[targetIdx - 1];
        if (!targetMinion) {
            std::cerr << "Error: No minion at target index" << std::endl;
            return;
        }
        minion->useAbility(targetMinion, nullptr);
    }
    // another if to check if its a summon effect
    // if it is supply board
    else if (minion->getAbility()->getEffect()->isSummonEffect()) {
        minion->useAbility(nullptr, &board);
    } else {
        // no target needed, just use the ability
        minion->useAbility();
    }
}

void Player::drawCard() {
    if (!hand.isFull() && !deck.isEmpty()) {
        Card* c = deck.draw();
        if (c) {
            hand.addCard(c);
        } else {
            std::cerr << "Error: Failed to draw card from deck." << std::endl;
        }
    }
}

