#include "Deck.h"
#include <fstream>
#include <iostream>
#include <vector>

void Deck::load_deck(const std::string& filename) {
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
}
