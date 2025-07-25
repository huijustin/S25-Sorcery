#include "BuffEffect.h"
#include <iostream>

BuffEffect::BuffEffect(Minion** targetSlot, std::function<Minion*(Minion*)> enchantmentApplicator)
    : targetSlot(targetSlot), enchantmentApplicator(std::move(enchantmentApplicator)) {}

void BuffEffect::setTarget(Minion* target) {
    if (targetSlot) {
        *targetSlot = target;
    }
}

void BuffEffect::apply() {
    if (targetSlot && *targetSlot) {
        Minion* current = *targetSlot;
        *targetSlot = enchantmentApplicator(current);  // Apply enchantment
        std::cout << "Applied enchantment to " << current->getName() << std::endl;
    } else {
        std::cerr << "BuffEffect failed: No valid target." << std::endl;
    }
}

std::unique_ptr<Effect> BuffEffect::clone() const {
    return std::make_unique<BuffEffect>(*this);
}

