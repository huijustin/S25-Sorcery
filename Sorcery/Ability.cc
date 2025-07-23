#include "Ability.h"

Ability::Ability(std::unique_ptr<Effect> effect, std::string description)
    : effect(std::move(effect)), description(std::move(description)) {}

Effect* Ability::getEffect() const {
    return effect.get();
}
std::string Ability::getDescription() const {
    return description;
}

