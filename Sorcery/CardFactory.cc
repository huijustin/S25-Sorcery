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
    // Novice Pyromancer
    std::unique_ptr<Effect> effect = std::make_unique<DamageEffect>(1); // Creates effect that deals 1 damage
    Ability* novicePyromancer = new ActivatedAbility(1, "Deal 1 damage", std::make_unique<DamageEffect>(1));

    // Minions                 CardID, Name,        Cost,ATK,Def,Ability,                  Card Text
    masterList.emplace_back(std::make_unique<Minion>(0, "Air Elemental", 0, 1, 1, nullptr, ""));
    masterList.emplace_back(std::make_unique<Minion>(1, "Earth Elemental", 3, 4, 4, nullptr, ""));
    masterList.emplace_back(std::make_unique<Minion>(2, "Bone Golem", 2, 1, 3, nullptr, "Gain +1/+1 whenever a minion leaves play"));
    masterList.emplace_back(std::make_unique<Minion>(3, "Fire Elemental", 2, 2, 2, nullptr, "When an opponent's minion enters play, deal 1 damage to it"));
    masterList.emplace_back(std::make_unique<Minion>(4, "Potion Seller", 2, 1, 3, nullptr, "At the end of your turn, all your minions gain +0/+1"));
    masterList.emplace_back(std::make_unique<Minion>(5, "Novice Pyromancer", 1, 0, 1, novicePyromancer, "Deal 1 damage to target minion"));
    masterList.emplace_back(std::make_unique<Minion>(6, "Apprentice Summoner", 1, 1, 1, nullptr, "Summon a 1/1 air elemental"));
    masterList.emplace_back(std::make_unique<Minion>(7, "Master Summoner", 3, 2, 3, nullptr, "Summon up to three 1/1 air elementals"));

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
