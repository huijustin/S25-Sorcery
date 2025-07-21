#include <algorithm>
#include <random>
#include <chrono>
#include "deck.h"

Deck::~Deck() { for (auto c : cards) delete c; }

Card* Deck::draw() {
    if (cards.empty()) return nullptr;
    Card: drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(cards.begin(), cards.end(), rng);
}

void Deck::addCard(Card* card) {
    cards.emplace_back(card);
}

bool Deck::isEmpty() const {
    return cards.empty();
}
