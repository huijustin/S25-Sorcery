#include "CardFactory.h"
#include "Minion.h"
#include "Spell.h"
#include <iostream>

CardFactory::CardFactory() {
    // Fill master list with one instance of each unique card

    // Create Ability effects
    // Create Minion Abilities

    // Minions                 CardID, Name,        Cost,ATK,Def,Ability,                  Card Text
    masterList.push_back(new Minion(0, "Air Elemental", 0, 1, 1, nullptr, ""));
    masterList.push_back(new Minion(1, "Earth Elemental", 3, 4, 4, nullptr, ""));
    masterList.push_back(new Minion(2, "Bone Golem", 2, 1, 3, nullptr, "Gain +1/+1 whenever a minion leaves play"));
    masterList.push_back(new Minion(3, "Fire Elemental", 2, 2, 2, nullptr, "Whenever an opponent's minion enters play, deal 1 damage to it"));
    masterList.push_back(new Minion(4, "Potion Seller", 2, 1, 3, nullptr, "At the end of your turn, all your minions gain +0/+1"));
    masterList.push_back(new Minion(5, "Novice Pyromancer", 1, 0, 1, nullptr, "Deal 1 damage to target minion"));
    masterList.push_back(new Minion(6, "Apprentice Summoner", 1, 1, 1, nullptr, "Summon a 1/1 air elemental"));
    masterList.push_back(new Minion(7, "Master Summoner", 3, 2, 3, nullptr, "Summon up to three 1/1 air elementals"));

    // Spells

    // Enchantment

    // Rituals
}

CardFactory::~CardFactory() {
    for (auto card : masterList) {
        delete card;
    }
}

const std::vector<Card*>& CardFactory::getMasterList() const {
    return masterList;
}

/* 
Card* CardFactory::cloneCard(const int ID) const {
    
    // Clone card at index

    // Fail to return card
    return nullptr;
}
*/