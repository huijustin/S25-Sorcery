#ifndef SPELL
#define SPELL
#include "Card.h"

class Spell : public Card {
public:
    Spell(int ID, std::string name, int cost);
    void activate();
    void play() override;
