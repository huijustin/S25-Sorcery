#include "Enchantment.h"
#include "ActivatedAbility.h"
#include <iostream>
#include <typeinfo>

Enchantment::Enchantment(Minion* base)
    : Minion(base->getID(), base->getName(), base->getCost(), base->getAttack(), base->getDefence(), 
    base->getAbility() ? base->getAbility()->clone() : nullptr, base->getCardText()),
      base(base) {}

Enchantment::~Enchantment() {
    if (base) delete base;
}

int Enchantment::getAttack() const {
    return base->getAttack();
}

int Enchantment::getDefence() const {
    return base->getDefence();
}

Minion* Enchantment::top() {
    return base->top();
}

Minion* Enchantment::getBase() {
    return base;
}

Minion* Enchantment::removeTopEnchantment(Minion* minion) {
    Enchantment* top = dynamic_cast<Enchantment*>(minion);
    if (!top) return minion;

    Minion* base = top->getBase();
    top->base = nullptr;
    delete top;
    return base;
}

Minion* Enchantment::removeAllEnchantments(Minion* minion) {
    while (dynamic_cast<Enchantment*>(minion)) {
        minion = removeTopEnchantment(minion);
    }
    return minion;
}

card_template_t Enchantment::getTemplate() const {
    Ability *ab = getAbility();

    card_template_t render;
    if (!ab) {
        render = display_minion_no_ability(name, cost, getAttack(), getDefence());
    } else if (auto* act = dynamic_cast<ActivatedAbility*>(ab)) {
        render = display_minion_activated_ability(name, cost, getAttack(), getDefence(), act->getActivationCost(), act->getDescription());
    } else {
        std::cerr << "Error: Unknown ability type for enchantment " << name << std::endl;
        render = display_minion_no_ability(name, cost, getAttack(), getDefence());
    }

    return render;
}
