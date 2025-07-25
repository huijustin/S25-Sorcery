#include "HasteEnchantment.h"
#include <iostream>

HasteEnchantment::HasteEnchantment(Minion* base) : Enchantment(base) {
    // Add 1 action upon application
    setActions(getActions() + 1);
    std::cout << getName() << " gains 1 extra action from Haste!" << std::endl;
}

void HasteEnchantment::roundStart() {
    base->roundStart(); 
    // Add Haste effect
    std::cout << getName() << " is Hasted! +1 action." << std::endl;
    setActions(getActions() + 1);
}
