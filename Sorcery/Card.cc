#include "Card.h"

Card::Card(int cost) : cost(cost) {}

int Card::getCost() {
    return cost;
}

Card::~Card() {}
