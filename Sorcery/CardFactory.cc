#include "CardFactory.h"
#include "Effect.h" 
#include "DamageEffect.h"  
#include "SummonEffect.h"
#include "Minion.h"
#include "Spell.h"
#include "ActivatedAbility.h"
#include "TriggerAbility.h"
#include <memory>
#include <iostream>

CardFactory::CardFactory() {
    // Fill master list with one instance of each unique card

    // Create Ability effects
    // Create Minion Abilities
    // Novice Pyromancer
    std::unique_ptr<Effect> effect = std::make_unique<DamageEffect>(1);
    ActivatedAbility novicePyromancer(1, "Deals 1 damage to ", std::move(effect));

    // Minions                 CardID, Name,        Cost,ATK,Def,Ability,                  Card Text
    masterList.push_back(new Minion(0, "Air Elemental", 0, 1, 1, nullptr, ""));
    masterList.push_back(new Minion(1, "Earth Elemental", 3, 4, 4, nullptr, ""));
    masterList.push_back(new Minion(2, "Bone Golem", 2, 1, 3, nullptr, "Gain +1/+1 whenever a minion leaves play"));
    masterList.push_back(new Minion(3, "Fire Elemental", 2, 2, 2, nullptr, "Whenever an opponent's minion enters play, deal 1 damage to it"));
    masterList.push_back(new Minion(4, "Potion Seller", 2, 1, 3, nullptr, "At the end of your turn, all your minions gain +0/+1"));
    masterList.push_back(new Minion(5, "Novice Pyromancer", 1, 0, 1, novicePyromancer, "Deal 1 damage to target minion"));
    masterList.push_back(new Minion(6, "Apprentice Summoner", 1, 1, 1, nullptr, "Summon a 1/1 air elemental"));
    masterList.push_back(new Minion(7, "Master Summoner", 3, 2, 3, nullptr, "Summon up to three 1/1 air elementals"));

    // Spells

    // Enchantment
    
    // Create Ritual effects
    // Rituals                CardID, Name, Cost, TriggerCount, Effect,                      Card Text
    // masterList.push_back(new Ritual());
}

CardFactory::~CardFactory() {
    for (auto card : masterList) {
        delete card;
    }
}

const std::vector<Card*>& CardFactory::getMasterList() const {
    return masterList;
}

Card* CardFactory::cloneCard(const int ID) const {
    
    // Clone card at index

    return nullptr;
}
