#ifndef HAND_H
#define HAND_H
#include <vector>
#include "Card.h"

class Hand {
    std::vector<Card*> hand;
    static const int MAX_SIZE = 5;
public:
    ~Hand();
    // adds card to hand, false if hand is full
    bool addCard(Card*);
    // remove and return the ith card, or nullptr if hand is empty
    Card* removeCard(int i);

    // accessors
    bool isFull() const;
    int getSize() const;
    Card* getCard(int i) const; 
    // return vector of cards for display
    const std::vector<Card*>& getCards() const;
};

#endif
