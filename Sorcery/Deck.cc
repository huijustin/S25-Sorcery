#include "Deck.h"
#include "CardFactory.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

extern CardFactory cardFactory;

void  Deck::load_deck(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open deck file: " << filename << std::endl;
        return;
    }

    std::string name;
    while (std::getline(file, name)) {
        if (name.empty()) continue;
        std::unique_ptr<Card> card = CardFactory->cloneCardByName(name);
        if (card) {
            cards.push_back(card.release());
        }
        else {
            std::cerr << "Unknown card name in deck file: " << name << std::endl;
        }

    }
}

Deck::~Deck() { for (auto c : cards) delete c; }

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card* Deck::draw() {
    if (cards.empty()) {
        std::cerr << "Deck is empty, cannot draw a card." << std::endl;
        return nullptr;
    }
    Card* drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

bool Deck::isEmpty() const {
    return cards.empty();
}
