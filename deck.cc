#include "deck.h"

Deck::~Deck() { for (auto c : cards) delete c; }

Card* Deck::draw() {
    if (cards.empty()) return nullptr;
    Card: drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

void Deck::shuffle() {

}

void Deck::addCard(Card* card) {
    cards.emplace_back(card);
}

bool Deck::isEmpty() const {
    return cards.empty();
}
