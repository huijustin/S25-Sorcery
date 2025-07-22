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

std::string Player::getName() const { return name; }
int Player::getLife() const { return life; }
int getMagic() const { return magic; }
void setLife(int l) { life = l; }
void setMagic(int m) { magic = m; }

void Player::takeDamage(int amount) { life -= amount; }
void Player::gainMagic(int amount) { magic += amount; }
void Player::spendMagic(int cost) { mgaic -= cost; }


void Player::startTurn() {
    gainMagic(1);
    drawCard();
    // TODO: trigger "start of turn" effects (rituals, triggers)
}

void Player::endTurn() {
    // TODO: trigger any “end of turn” ritual or minion triggers
}

void Player::playCard(int idx) {
    Card* c = hand.removeCard(idx);
    if (!c) {
        std::cerr << "Error: cannot play card" << std::endl;
        return;
    }
    spendMagic(c->getCost());
    c->play();
    // TODO: place c on board, graveyard, or ritual slot based on dynamic type
}

void Player::attack(int fromIdx, int toIdx) {
    if (fromIdx < 1 || fromIdx > board.size()) {
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
    if (fromIdx < 1 || fromIdx > board.size()) {
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

