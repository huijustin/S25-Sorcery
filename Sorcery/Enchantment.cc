#include "Enchantment.h"
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
    return base->getTemplate();
}
