#pragma once
#include <vector>
#include <string>
#include "Card.h"

class CardFactory {
    std::vector<Card*> masterList;

public:
    CardFactory();
    ~CardFactory();

    const std::vector<Card*>& getMasterList() const;

    // might need this later depening on implementation
    //Card* cloneCard(const int ID) const; 
};