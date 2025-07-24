#include "MagicFatigueEnchantment.h"
#include "ActivatedAbility.h"
#include <iostream>

MagicFatigueEnchantment::MagicFatigueEnchantment(Minion* base)
    : Enchantment(base) {
    std::cout << getName() << " is affected by Magic Fatigue! Ability costs 2 more mana." << std::endl;
}

Ability* MagicFatigueEnchantment::getAbility() const {
    Ability* original = base->getAbility();
    if (!original) return nullptr;

    // Only supports ActivatedAbility for now
    auto* act = dynamic_cast<ActivatedAbility*>(original);
    if (!act) return original;

    int newCost = act->getActivationCost() + 2;
    std::string desc = act->getDescription() + " (Magic Fatigue +2)";
    
    // Create a new ability with same effect but higher cost
    return new ActivatedAbility(newCost,desc,act->cloneEffect());
}
