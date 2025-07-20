#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"

class Deck {
    std::vector<Card*> cards;
  public:
    ~Deck();

    // pops one card or nullptr if deck is empty
    Card* draw();
    // shuffles the deck
    void shuffle();
    // add a card to deck
    void addCard(Card* card);
    bool isEmpty() const;
}

#endif
