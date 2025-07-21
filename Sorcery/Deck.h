#ifndef DECK_H
#define DECK_H
#include <vector>
#include <string>
#include "Card.h"

class Deck {
    std::vector<Card*> hand;
public:
    ~Deck();

    // pops one card or nullptr if deck is empty
    Card* draw();
    // shuffles the deck
    void shuffle();
    // returns true if deck is empty, else false
    bool isEmpty() const;
    // loads card names from file and use CardFactory to create cards
    void load_deck(const std::string& filename);

};

#endif
