#include "Ritual.h"
#include "Player.h"
#include <iostream>

Ritual::Ritual(int id, std::string name, int cost, std::string triggerCondition, int charges)
    : Card(id, name, cost, "Ritual: " + triggerCondition), activationCost(cost), charges(charges),
      triggerCondition(triggerCondition) {}

void Ritual::play() {
    std::cout << "Error: No player provided to Ritual" << std::endl;
}

void Ritual::play(Player* owner) {
    if (!owner) {
        std::cerr << "Error: No player provided to Ritual" << std::endl;
        return;
    }

    // Clone and assign to the player's ritual slot
    owner->setRitual(std::unique_ptr<Ritual>(dynamic_cast<Ritual*>(this->clone().release())));
    std::cout << "Ritual " << name << " has been played and assigned to player " << owner->getName() << "." << std::endl;
}

int Ritual::getCost() { return cost; }

int Ritual::getCharges() const { return charges; }

std::string Ritual::getTriggerCondition() const { return triggerCondition; }

std::unique_ptr<Card> Ritual::clone() const {
    return std::make_unique<Ritual>(*this);
}
