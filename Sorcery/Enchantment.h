#pragma once
#include "Minion.h"
#include "ascii_graphics.h"


class Enchantment : public Minion {
protected:
    Minion* base;

public:
    Enchantment(Minion* base);
    ~Enchantment() override;

    int getAttack() const override;
    int getDefence() const override;
    Minion* top() override; // Access base minion (does NOT delete enchantments from memory)
    Minion* getBase();  // Access minion with topmost layer removed (does NOT delete enchantments from memory)

    static Minion* removeTopEnchantment(Minion* minion);
    static Minion* removeAllEnchantments(Minion* minion);
    card_template_t getTemplate() const override;
};
