#include "BuffEffect.h"
#include <iostream>
#include "Minion.h"

BuffEffect::BuffEffect(Minion** targetSlot, std::function<Minion*(Minion*)> enchantmentApplicator)
    : targetSlot(targetSlot), enchantmentApplicator(std::move(enchantmentApplicator)) {}

void BuffEffect::setTarget(Minion* target) {
    if (!targetSlot) {
        std::cerr << "Error: targetSlot is nullptr in BuffEffect::setTarget." << std::endl;
        return;
    }
    *targetSlot = target;
}
void BuffEffect::setSlotPointer(Minion** ptr) {
    targetSlot = ptr;
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
    // cloned effect will need targetSlot to be re-set later
    return std::make_unique<BuffEffect>(nullptr, enchantmentApplicator);
}
