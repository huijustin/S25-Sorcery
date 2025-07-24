#ifndef SPELL
#define SPELL

#include "Card.h"
#include "Effect.h"
#include "Minion.h"
#include <memory>
#include <string>

class Spell : public Card {
    std::unique_ptr<Effect> effect;

public:
    Spell(int id, std::string name, int cost, std::string text, std::unique_ptr<Effect> effect);

    void play() override;              // required by base class
    void play(Minion* target);         // overload for targeted spells
};

#endif
