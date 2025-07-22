#include "Card.h"
#include <string>

Card::Card(int ID, std::string name, int cost) 
    : cardID(ID), name(name), cost(cost) {}

int Card::getCost() {
    return cost;
}

int Card::getID() {
    return cardID;
}

std::string Card::getName() {
    return name;
}

Card::~Card() {}
