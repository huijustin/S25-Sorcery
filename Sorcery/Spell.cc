#include "Spell.h"
#include <iostream>

Spell::Spell(int id, std::string name, int cost, std::string text, std::unique_ptr<Effect> effect)
    : Card(id, std::move(name), cost, std::move(text)), effect(std::move(effect)) {}

void Spell::play() {
    play(nullptr); // default to no target
}

void Spell::play(Minion* target) {
    if (effect) {
        if (effect->supportsTarget()) {
            effect->setTarget(target);
        }
        effect->apply();
        std::cout << getName() << " is played: " << cardText << std::endl;
    } else {
        std::cerr << "Error: Spell has no effect." << std::endl;
    }
}

Effect* Spell::getEffect() const {
    return effect.get();
}
