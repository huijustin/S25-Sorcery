#include "hand.h"

Hand::~Hand() { for (auto c : cards) delete c; }

bool Hand::addCard(Card *card) {
    if (isFull()) return false;
    cards.emplace_back(card);
    return true;
}

Card* Hand::removeCard(int i) {
    if (i >= cards.size() || i < 0) return nullptr;
    Card* c = cards[i];
    cards.erase(cards.begin() + i);
    return c;
}

bool Hand::isFull() const { return cards.size() >= maxSize; }
int Hand::size() const { return cards.size(); }
