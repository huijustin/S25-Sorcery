#include "Card.h"
#include <string>

Card::Card(int ID, std::string name, int cost, std::string cardText) 
    : cardID(ID), name(name), cost(cost), cardText(cardText) {}

int Card::getCost() {
    return cost;
}

int Card::getID() {
    return cardID;
}

std::string Card::getName() const{
    return name;
}

std::string Card::getCardText() const { 
    return cardText; 
}

Card::~Card() {}
