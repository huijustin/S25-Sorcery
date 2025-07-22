#include "Hand.h"
#include <iostream>

Hand::~Hand() { for (auto c : hand) delete c; }

bool Hand::addCard(Card *card) {
    if (isFull()) {
        std::cerr << "Hand is full, cannot add card." << std::endl;
        return false;
    }
    hand.emplace_back(card);
    return true;
}

Card* Hand::removeCard(int i) {
    if (i > hand.size() || i < 1) {
        std::cerr << "Invalid index for removing card: " << i << " in Hand" << std::endl;
        return nullptr;
    }
    if (hand.empty()) {
        std::cerr << "Hand is empty, cannot remove card." << std::endl;
        return nullptr;
    }
    Card* c = hand[i - 1];
    hand.erase(hand.begin() + (i - 1));
    return c;
}

bool Hand::isFull() const { return hand.size() >= MAX_HAND_SIZE; }
int Hand::getSize() const { return hand.size(); }

Card* Hand::getCard(int i) const {
    if (i > hand.size() || i < 1) {
        std::cerr << "Invalid index for getting card: " << i << " in Hand" << std::endl;
        return nullptr;
    } else {
        return hand[i - 1];
    }
}

const std::vector<Card*>& Hand::getCards() const { return hand; }

