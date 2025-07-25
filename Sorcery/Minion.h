#pragma once
#include "Card.h"
#include "Ability.h"
#include "ascii_graphics.h"
#include <vector>

class Player;
class Board;
class Enchantment;

class Minion : public Card {
protected:
    int attack;
    int defence;
    int actions;
    std::string cardText;

    std::unique_ptr<Ability> ability;
    std::vector<std::unique_ptr<Card>> enchantmentStack;

public:
    Minion(int ID, std::string name, int cost, int attack, int defence, std::unique_ptr<Ability> ability, std::string cardText);
    virtual ~Minion();

    void attackMinion(Minion* targetMinion);
    void attackPlayer(Player* targetPlayer);

    // Minions can take damage from multiple sources so create a takeDamage method
    void takeDamage(int dmg); 

    void trigger(const std::string& eventString);
    void play() override;

    virtual Ability* getAbility() const;

    // Optional target and baord
    virtual void useAbility(Minion* target = nullptr, Board* board = nullptr);

    virtual Minion* top();

    virtual void roundStart(); // Run at roundstart to reset actions
    void roundEnd();
    std::unique_ptr<Card> clone() const;

    // Simple Get functions
    virtual int getAttack() const;
    virtual int getDefence() const;
    int getActions() const;
    void setActions(int a);
    void useActions(int a);
    Enchantment* topEnchantment();
    std::vector<Card*> getEnchantmentStack() const;
    void addEnchantmentCard(std::unique_ptr<Card> spellCard);

    virtual std::unique_ptr<Minion> cloneMinion() const;

    // rendering methods
    card_template_t getTemplate() const override;
}; 
