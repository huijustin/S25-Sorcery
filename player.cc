#include "player.h"

Player::Player(const std::string &name) : 
    name{name}, life{20}, magic{3} {}

bool Player::drawCard() {    
    if (deck.isEmpty() || hand.isFull()) return false;
    Card* newCard = deck.draw();
    return hand.addCard(newCard);
}

void Player::startTurn() {
    magic += 1;
    drawCard();
    // implement start of turn trigger
}

void Player::endTurn() {
    // implement end of turn trigger
}

std::string Player::getName() const { return name; }
int Player::getLife() const { return life; }
void Player::setLife(int life) { this->life = life; }
int Player::getMagic() const { return magic; }
void Player::setMagic(int magic) { this->magic = magic; }

