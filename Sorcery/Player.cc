#include "Player.h"
#include "Spell.h"
#include "BuffEffect.h"
#include "SummonEffect.h"
#include <utility>
#include <iostream>

/* Ctor and Dtor */

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

Player::~Player() {}

std::string Player::getName() const { return name; }
int Player::getLife() const { return life; }
int Player::getMagic() const { return magic; }
Ritual* Player::getRitual() const { return ritual.get(); }
const Graveyard* Player::getGraveyard() const { return graveyard; }
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
    if (getRitual()) {
        getRitual()->trigger("Start of Turn", this);
    }
}

void Player::endTurn() {
    // TODO: trigger any “end of turn” ritual or minion triggers
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

void Player::setRitual(std::unique_ptr<Ritual> newRitual) {
    ritual = std::move(newRitual);
}
