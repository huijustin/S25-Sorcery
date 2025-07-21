#include "Card.h"

Hand::~Hand() { for (auto c : hand) delete c; }

bool Hand::addCard(Card *card) {
    if (isFull()) return false;
    Hand.emplace_back(card);
    return true;
}

Card* Hand::removeCard(int i) {
    if (i > hand.size() || i < 1) return nullptr;
    Card* c = hand[i - 1];
    hand.erase(hand.begin() + (i - 1));
    return c;
}

bool isFull() const { return hand.size() >= MAX_SIZE; }

int getSize() const { return Hand.size(); }

Card* Hand::getCard(int i) const {
    if (i > hand.size() || i < 1) {
        return nullptr;
    } else {
        return Hand[i - 1];
    }
}

const std::vector<Card*>& getCards() const { return hand; }

