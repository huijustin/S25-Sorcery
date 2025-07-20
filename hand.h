#ifndef HAND_H
#define HAND_H
#include <vector>
#include "card.h"

class Hand {
    std::vector<Card*> cards;
    const int maxSize = 5;
  public:
    ~Hand();
    // adds card to the hand, false if hand is full
    bool addCard(Card *card);
    // remove and return the ith card, or nullptr
    Card* removeCard(int i);

    bool isFull() const;
    int size() const;
}

#endif
