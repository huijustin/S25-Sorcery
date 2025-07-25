#include "CardFactory.h"
#include "Effect.h" 
#include "Ability.h"
#include "ActivatedAbility.h"
#include "TriggerAbility.h"
#include "DamageEffect.h"  
#include "SummonEffect.h"
#include "BuffEffect.h"
#include "GiantStrengthEnchantment.h"
#include "EnrageEnchantment.h"
#include "HasteEnchantment.h"
#include "MagicFatigueEnchantment.h"
#include "SilenceEnchantment.h"
#include "Ritual.h"
#include "DarkRitual.h"
#include "Minion.h"
#include "Spell.h"
#include <memory>
#include <iostream>

CardFactory::CardFactory() {
    // Fill master list with one instance of each unique card

    // Create Ability effects
    // Create Minion Abilities
    
    Board* boardPlaceholder = nullptr;
    Minion* enchantTarget = nullptr;

    // Minions                                   CardID, Name,        Cost,ATK,Def,Ability,                  Card Text
    masterList.emplace_back(std::make_unique<Minion>(0, "Air Elemental", 0, 1, 1, nullptr, ""));
    masterList.emplace_back(std::make_unique<Minion>(1, "Earth Elemental", 3, 4, 4, nullptr, ""));

    masterList.emplace_back(std::make_unique<Minion>(2, "Bone Golem", 2, 1, 3, nullptr, "Gain +1/+1 whenever a minion leaves play"));
    masterList.emplace_back(std::make_unique<Minion>(3, "Fire Elemental", 2, 2, 2, nullptr, "When an opponent's minion enters play, deal 1 damage to it"));
    masterList.emplace_back(std::make_unique<Minion>(4, "Potion Seller", 2, 1, 3, nullptr, "At the end of your turn, all your minions gain +0/+1"));
        // Novice Pyromancer
    auto novicePyromancer = std::make_unique<ActivatedAbility>(1, "Deal 1 damage", std::make_unique<DamageEffect>(1)); // Creates effect that deals 1 damage
    masterList.emplace_back(std::make_unique<Minion>(5, "Novice Pyromancer", 1, 0, 1, std::move(novicePyromancer), "Deal 1 damage to target minion"));
        // Apprentice Summoner
    auto apprenticeSummoner = std::make_unique<ActivatedAbility>(1, "Summon 1 Air Elemental", std::make_unique<SummonEffect>(dynamic_cast<Minion*>(getMasterList()[0].get()), 1, boardPlaceholder));
    masterList.emplace_back(std::make_unique<Minion>(6, "Apprentice Summoner", 1, 1, 1, std::move(apprenticeSummoner), "Summon a 1/1 air elemental"));
        // Master Summoner
    auto masterSummoner = std::make_unique<ActivatedAbility>(1, "Summon 3 Air Elementals", std::make_unique<SummonEffect>(dynamic_cast<Minion*>(getMasterList()[0].get()), 3, boardPlaceholder));
    masterList.emplace_back(std::make_unique<Minion>(7, "Master Summoner", 3, 2, 3, std::move(masterSummoner), "Summon up to three 1/1 air elementals"));
    
    // Spells
    
    // Enchantment (Effectively the same as spell cards)
        // Giant Strength
    auto giantStrength = std::make_unique<BuffEffect>(&enchantTarget, [](Minion* base) { return new GiantStrengthEnchantment(base); });
    masterList.emplace_back(std::make_unique<Spell>(14, "Giant Strength", 1, "Give a minion +2/+2", std::move(giantStrength))); 
        // Enrage
    auto enrage = std::make_unique<BuffEffect>(&enchantTarget, [](Minion* base) { return new EnrageEnchantment(base); });
    masterList.emplace_back(std::make_unique<Spell>(15, "Enrage", 2, "Give a minion *2/*2", std::move(enrage))); 
        // Haste
    auto haste = std::make_unique<BuffEffect>(&enchantTarget, [](Minion* base) { return new HasteEnchantment(base); });
    masterList.emplace_back(std::make_unique<Spell>(16, "Haste", 1, "Minion gains +1 action each turn", std::move(haste))); 
        // Magic Fatigue
    auto magicFatigue = std::make_unique<BuffEffect>(&enchantTarget,[](Minion* base) { return new MagicFatigueEnchantment(base); });
    masterList.emplace_back(std::make_unique<Spell>(17,"Magic Fatigue",1,"Minion abilities cost +2 mana",std::move(magicFatigue)));
        // Silence
    auto silence = std::make_unique<BuffEffect>(&enchantTarget,[](Minion* base) { return new SilenceEnchantment(base); });
    masterList.emplace_back(std::make_unique<Spell>(18,"Silence",1,"Minion cannot use abilities",std::move(silence)));
    
    // Rituals
        // Dark Ritual ID 19
    masterList.emplace_back(std::make_unique<DarkRitual>());
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

CardFactory Factory; // Global instance of CardFactory
