#pragma once
#include <string>
#include "Card.h"

class CardFactory {
public:
    Card* createCard(std::string name);
};
