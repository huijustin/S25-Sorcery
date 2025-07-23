#include "Ability.h"

Ability::Ability(std::unique_ptr<Effect> effect)
    : effect(std::move(effect)) {}

Effect* Ability::getEffect() const {
    return effect.get();
}
std::string Ability::getDescription() const {
    return description;
}

