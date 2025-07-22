#include "Player.h"
#include <iostream>

Player::Player(const std::string &name, const std::string& deckFile) :
  name{name}, life{20}, magic{3}, ritual{nullptr} {
    deck.load_deck(deckFile);
    deck.shuffle();
    for (int i = 0; i < 5; ++i) {
        drawCard();
    }
}

Player::~Player() { delete ritual; }

std::string Player::getName() const { return name; }
int Player::getLife() const { return life; }
int Player::getMagic() const { return magic; }

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
    Card *c = hand.getCard(idx);
    if (!c) {
        std::cerr << "Error: Invalid card index or Hand is empty" << std::endl;
        return;
    }
    if (c->getCost() > magic) {
        std::cerr << "Error: Not enough magic to play this card." << std::endl;
        return;
    }
    if (idx < 1 || idx > hand.getSize()) {
        std::cerr << "Error: Invalid card index." << std::endl;
        return;
    }
    // Check if the card is a Ritual
    if (Ritual* ritualCard = dynamic_cast<Ritual*>(c)) {
        if (ritual) {
            std::cerr << "Error: Ritual slot is already occupied." << std::endl;
            return;
        }
        ritual = ritualCard; // Set the ritual
        Card *toPlay = hand.removeCard(idx); // Remove from hand
        ritual->play(); // Play the ritual
        return;
    }
    // Check if the card is a Minion
    if (Minion* minionCard = dynamic_cast<Minion*>(c)) {
        if (!board.addMinion(minionCard)) { 
            std::cerr << "Error: Board is full, cannot add minion." << std::endl;
            return;
        }
        Card *toPlay = hand.removeCard(idx); // Remove from hand
        minionCard->play(); // Play the minion
        return;
    }
    // For other card types, just play the card
    if (hand.isFull()) {
        std::cerr << "Error: Hand is full, cannot play this card." << std::endl;
        return;
    }
    // Check if the card is a spell or ability
    if (c->getCost() > magic) {
        std::cerr << "Error: Not enough magic to play this card." << std::endl;
        return;
    }
    // Proceed to play the card
    Card *toPlay = hand.removeCard(idx);
    spendMagic(c->getCost()); // Deduct magic cost
    c->play();  

    // TODO: place c on board, graveyard, or ritual slot based on dynamic type
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
}

void Player::drawCard() {
    if (!hand.isFull() && !deck.isEmpty()) {
        Card* c = deck.draw();
        hand.addCard(c);
    }
}

