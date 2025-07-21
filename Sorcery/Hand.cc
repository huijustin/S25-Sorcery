#include "Card.h"

Hand::~Hand() { for (auto c : hand) delete c; }

bool Hand::addCard(Card *card) {
    if (isFull()) return false;
    Hand.emplace_back(card);
    return true;
}

Card* Hand::removeCard(int i) {
    if (i >= hand.size() || i < 0) return nullptr;
    Card* c = hand[i];
    hand.erase(hand.begin() + i);
    return c;
}

bool isFull() const { return hand.size() >= maxSize; }

int getSize() const { return Hand.size(); }

Card* Hand::getCard(int i) const {
    if (i >= hand.size() || i < 0) {
        return nullptr;
    } else {
        return Hand[i];
    }
}

const std::vector<Card*>& getCards() const { return hand; }

