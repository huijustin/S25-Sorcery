#include "CardFactory.h"
#include "Effect.h" 
#include "Ability.h"
#include "ActivatedAbility.h"
#include "TriggerAbility.h"
#include "DamageEffect.h"  
#include "SummonEffect.h"
#include "Minion.h"
#include "Spell.h"
#include <memory>
#include <iostream>

CardFactory::CardFactory() {
    // Fill master list with one instance of each unique card

    // Create Ability effects
    // Create Minion Abilities
    
    Board* boardPlaceholder = nullptr;

    // Minions                                   CardID, Name,        Cost,ATK,Def,Ability,                  Card Text
    masterList.emplace_back(std::make_unique<Minion>(0, "Air Elemental", 0, 1, 1, nullptr, ""));
    masterList.emplace_back(std::make_unique<Minion>(1, "Earth Elemental", 3, 4, 4, nullptr, ""));
    masterList.emplace_back(std::make_unique<Minion>(2, "Bone Golem", 2, 1, 3, nullptr, "Gain +1/+1 whenever a minion leaves play"));
    masterList.emplace_back(std::make_unique<Minion>(3, "Fire Elemental", 2, 2, 2, nullptr, "When an opponent's minion enters play, deal 1 damage to it"));
    masterList.emplace_back(std::make_unique<Minion>(4, "Potion Seller", 2, 1, 3, nullptr, "At the end of your turn, all your minions gain +0/+1"));
        // Novice Pyromancer
    Ability* novicePyromancer = new ActivatedAbility(1, "Deal 1 damage", std::make_unique<DamageEffect>(1)); // Creates effect that deals 1 damage
    masterList.emplace_back(std::make_unique<Minion>(5, "Novice Pyromancer", 1, 0, 1, novicePyromancer, "Deal 1 damage to target minion"));
        // Apprentice Summoner
    Ability* apprenticeSummoner = new ActivatedAbility(1, "Summon 1 Air Elemental", std::make_unique<SummonEffect>(getMasterList()[0], 1, boardPlaceholder));
    masterList.emplace_back(std::make_unique<Minion>(6, "Apprentice Summoner", 1, 1, 1, apprenticeSummoner, "Summon a 1/1 air elemental"));
        // Master Summoner
    Ability* masterSummoner = new ActivatedAbility(1, "Summon 3 Air Elementals", std::make_unique<SummonEffect>(getMasterList()[0], 3, boardPlaceholder));
    masterList.emplace_back(std::make_unique<Minion>(7, "Master Summoner", 3, 2, 3, masterSummoner, "Summon up to three 1/1 air elementals"));

    // Spells

    // Enchantment
    
    // Create Ritual effects
    // Rituals                CardID, Name, Cost, TriggerCount, Effect,                      Card Text
    // masterList.push_back(new Ritual());
}

CardFactory::~CardFactory() {}

const std::vector<std::unique_ptr<Card>>& CardFactory::getMasterList() const {
    return masterList;
}

std::unique_ptr<Card> CardFactory::cloneCardByID(int id) const {
    for (const auto& card : masterList) {
        if (card->getID() == id) {
            return card->clone();
        }
    }
    return nullptr;
}

std::unique_ptr<Card> CardFactory::cloneCardByName(const std::string& name) const {
    for (const auto& card : masterList) {
        if (card->getName() == name) {
            return card->clone();
        }
    }
    return nullptr;
}
