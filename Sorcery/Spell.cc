#include Spell.h
#include <iostream>

Spell::Spell(int ID, std::string name, int cost)
    : Card(ID, std::move(name), cost) {}

void Spell::activate() {
    std::cout << getName() << " effect activated!" << std::endl;
}

void Spell::play() {
    std::cout << "Playing Spell: " << getName() << std::endl;
    activate();
}
