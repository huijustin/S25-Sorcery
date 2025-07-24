#include "Deck.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>


void  Deck::load_deck(const std::string& filename) {
    
    /*
    std::ifstream file(filename);
    std::string line;

    if (!(file.is_open())) {
        std::cerr << "Could not open deck file: " << filename << std::endl; // Check Error message
        return;
    }

    while (std::getline(file, line)) {

        std::cout << "loaded card: " << line << std::endl; // Check message
    }

    file.close();
    */
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
