#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "Board.h"
#include "Graveyard.h"
#include "Ritual.h"
#include "Minion.h"
#include "GameEngine.h"
#include "Spell.h"
#include "ActivatedAbility.h"
#include "BuffEffect.h"
#include "SummonEffect.h"
#include <utility>
#include <iostream>

/* Ctor and Dtor */

Player::Player(const std::string &name, Deck* deck, GameEngine* game)
    : name{name}, life{20}, magic{3}, deck{deck}, 
      hand{new Hand()}, board{new Board()}, graveyard{new Graveyard()}, ritual{nullptr}, game{game}, firsTurn{true} {
    if (!game) {
        std::cerr << "Error: GameEngine pointer is null." << std::endl;
        throw std::invalid_argument("GameEngine pointer cannot be null");
    }
    if (!game->isTestingMode()) {
        deck->shuffle();
    }
    for (int i = 0; i < 5; ++i) {
        drawCard();
    }
}

Player::~Player() {
    delete deck;
    delete hand;
    delete board;
    delete graveyard;
    // ritual is managed by unique_ptr, no need to delete
    // game is not owned by Player, so we don't delete it
}

std::string Player::getName() const { return name; }
int Player::getLife() const { return life; }
int Player::getMagic() const { return magic; }
Ritual* Player::getRitual() const { return ritual.get(); }
const Graveyard* Player::getGraveyard() const { return graveyard; }
Board* Player::getBoard() const { return board; }
Hand* Player::getHand() const { return hand; }


void Player::takeDamage(int amount) { 
    life -= amount; 
    if (life <= 0) {
        life = 0;
        if (game) {
            game->playerDefeated(this);
        }
    }
}
void Player::gainMagic(int amount) { magic += amount; }
void Player::spendMagic(int cost) { magic -= cost; }


void Player::startTurn() {
    if (firsTurn) {
        firsTurn = false;
    } else {
        gainMagic(1);
    }
    drawCard();
    if (getRitual()) {
        getRitual()->trigger("Start of Turn", this);
    }
    getBoard()->resetActions();
}

void Player::endTurn() {
    // TODO: trigger any “end of turn” ritual or minion triggers
}

void Player::playCard(int idx) {
    Card* card = hand->getCard(idx);

    if (!card) {
        std::cerr << "Error: No card at index " << idx << std::endl;
        return;
    }

    int cost = card->getCost();
    if (!game->isTestingMode() && cost > magic) {
        std::cerr << "Error: Not enough magic to play card " << card->getName() << std::endl;
        return;
    }

    if (auto *spell = dynamic_cast<Spell*>(card)) {
        auto *effect = spell->getEffect();
        if (effect && effect->supportsTarget()) {
            std::cerr << "Error: Spell " << spell->getName() << " requires a target." << std::endl;
            return;
        }
    }

    if (!game->isTestingMode()) {
        spendMagic(cost);
    }

    card = hand->removeCard(idx);

    // check if the card is a minion
    if (auto* minion = dynamic_cast<Minion*>(card)) {
        if (!board->addMinion(minion)) {
            std::cerr << "Error: Board is full, cannot play minion " << minion->getName() << std::endl;
            hand->addCard(card); // Return the card back to hand
            return;
        }
        minion->play();
    } 
    // check if the card is a ritual
    else if (auto ritualCard = dynamic_cast<Ritual*>(card)) {
        ritualCard->play(this);
        ritual = std::unique_ptr<Ritual>(dynamic_cast<Ritual*>(ritualCard->clone().release()));
    }
    // else it is a spell
    else if (auto* spell = dynamic_cast<Spell*>(card)) {
        spell->play();
        delete spell;
    } else {
        std::cerr << "Error: Unknown card type for card " << card->getName() << std::endl;
        hand->addCard(card); // Return the card back to hand
    }

    // update board and graveyard
    cleanupDeadMinions();
    game->getInactivePlayer()->cleanupDeadMinions();
}

void Player::playCard(int idx, Player* target, int cardIdx) {
    Card* card = hand->getCard(idx);

    if (!card) {
        std::cerr << "Error: No card at index " << idx << std::endl;
        return;
    }

    int cost = card->getCost();
    if (!game->isTestingMode() && cost > magic) {
        std::cerr << "Error: Not enough magic to play card " << card->getName() << std::endl;
        return;
    }

    if (!game->isTestingMode() && cost > magic) {
        std::cerr << "Error: Not enough magic to play card " << card->getName() << std::endl;
        return;
    }
    if (!game->isTestingMode()) {
        spendMagic(cost);
    }

    card = hand->removeCard(idx);

    Minion* targetMinion = nullptr;
    if (cardIdx > 0) {
        const auto targetBoard = target->getBoard()->getMinions();
        if (cardIdx >= 1 && cardIdx <= static_cast<int>(targetBoard.size())) {
            targetMinion = targetBoard[cardIdx - 1];
        }
    }

    // check if the card is a spell
    if (auto* spell = dynamic_cast<Spell*>(card)) {
        // If buff
        if (auto* buff = dynamic_cast<BuffEffect*>(spell->getEffect())) {
            if (!targetMinion) {
                std::cerr << "BuffEffect requires a target minion, but none provided." << std::endl;
                hand->addCard(card); // Return the card back to hand
                return;
            }

            // Get the actual minion slot pointer on the board
            Minion*& boardSlot = board->getMinions()[cardIdx - 1];

            // Inject correct slot pointer into effect
            buff->setSlotPointer(&boardSlot);
            buff->setTarget(boardSlot);
            buff->apply();

            // Also record the enchantment on the minion for later undo/display
            boardSlot->addEnchantmentCard(spell->clone());

            std::cout << "Applied BuffEffect from spell: " << spell->getName() << " to " << boardSlot->getName() << std::endl;
        } else {
            // Normal non-buff spell
            spell->play(targetMinion);
        }
        delete spell;
    } 
    // check if the card is a minion
    else if (auto* minion = dynamic_cast<Minion*>(card)) {
        if (!board->addMinion(minion)) {
            std::cerr << "Error: Board is full, cannot play minion " << minion->getName() << std::endl;
            hand->addCard(card); // Return the card back to hand
            return;
        }
        minion->play();
    } 
    // check if the card is a ritual
    else if (auto ritualCard = dynamic_cast<Ritual*>(card)) {
        ritualCard->play(this);
        ritual = std::unique_ptr<Ritual>(dynamic_cast<Ritual*>(ritualCard->clone().release()));
    } else {
        std::cerr << "Error: Unknown card type for card " << card->getName() << std::endl;
        hand->addCard(card); // Return the card back to hand
    }

    // update board and graveyard
    cleanupDeadMinions();
    target->cleanupDeadMinions();
}

void Player::attack(int idx) {
    const auto& minions = board->getMinions();
    if (idx < 1 || idx > static_cast<int>(minions.size())) {
        std::cerr << "Error: Invalid minion index " << idx << std::endl;
        return;
    }

    Minion* attacker = minions[idx - 1];
    if(!attacker || attacker->getActions() <= 0) {
        std::cerr << "Error: this minion cannot attack or does not exist." << std::endl;
        return;
    }
    Player* opponent = game->getInactivePlayer();
    attacker->attackPlayer(opponent);
    attacker->useActions(1);

    // check for minions that may have died
    cleanupDeadMinions();
    opponent->cleanupDeadMinions();
}

void Player::attack(int fromIdx, int toIdx) {
    const auto& myMinions = board->getMinions();
    if (fromIdx < 1 || fromIdx > static_cast<int>(myMinions.size())) {
        std::cerr << "Error: Invalid attacking minion index " << fromIdx << std::endl;
        return;
    }

    Player* opponent = game->getInactivePlayer();
    const auto& opponentMinions = opponent->getBoard()->getMinions();
    if (toIdx < 1 || toIdx > static_cast<int>(opponentMinions.size())) {
        std::cerr << "Error: Invalid defending minion index " << toIdx << std::endl;
        return;
    }

    Minion* attacker = myMinions[fromIdx - 1];
    Minion* defender = opponentMinions[toIdx - 1];
    if (!attacker || attacker->getActions() <= 0) {
        std::cerr << "Error: this minion cannot attack or does not exist." << std::endl;
        return;
    }

    attacker->attackMinion(defender);
    attacker->useActions(1);

    // check for minions that may have died
    cleanupDeadMinions();
    opponent->cleanupDeadMinions();
}

void Player::useAbility(int idx) {
    const auto& minions = board->getMinions();
    if (idx < 1 || idx > static_cast<int>(minions.size())) {
        std::cerr << "Error: Invalid minion index " << idx << std::endl;
        return;
    }

    Minion* m = minions[idx - 1];
    auto action = dynamic_cast<ActivatedAbility*>(m->getAbility());
    if (action) {
        int cost = action->getActivationCost();
        if (!game->isTestingMode() && cost > magic) {
            std::cerr << "Error: Not enough magic to use ability of " << m->getName() << std::endl;
            return;
        }
        if (!game->isTestingMode()) {
            spendMagic(cost);
        }
        m->useAbility(nullptr, board);
        // check for minions that may have died
        cleanupDeadMinions();
        game->getInactivePlayer()->cleanupDeadMinions();
    } else {
        std::cerr << "Error: Minion " << m->getName() << " does not have an activated ability." << std::endl;
        return;
    }
}

void Player::useAbility(int idx, Player* target, int cardIdx) {
    const auto& minions = board->getMinions();
    if (idx < 1 || idx > static_cast<int>(minions.size())) {
        std::cerr << "Error: Invalid minion index " << idx << std::endl;
        return;
    }

    Minion* m = minions[idx - 1];
    auto* action = dynamic_cast<ActivatedAbility*>(m->getAbility());
    if (action) {
        int cost = action->getActivationCost();
        if (!game->isTestingMode() && cost > magic) {
            std::cerr << "Error: Not enough magic to use ability of " << m->getName() << std::endl;
            return;
        }
        if (!game->isTestingMode()) {
            spendMagic(cost);
        }
    }
    Minion* targetMinion = nullptr;
    if (cardIdx > 0) {
        const auto& enemy = target->board->getMinions();
        if (cardIdx >= 1 && cardIdx <= static_cast<int>(enemy.size())) {
            targetMinion = enemy[cardIdx - 1];
        }
    }

    m->useAbility(targetMinion, board);

    // check for minions that may have died
    cleanupDeadMinions();
    target->cleanupDeadMinions();
}

void Player::drawCard() {
    if (!hand->isFull() && !deck->isEmpty()) {
        Card* c = deck->draw();
        if (c) {
            hand->addCard(c);
        } else {
            std::cerr << "Error: Failed to draw card from deck." << std::endl;
        }
    }
}

void Player::setRitual(std::unique_ptr<Ritual> newRitual) {
    ritual = std::move(newRitual);
}

void Player::cleanupDeadMinions() {
    for (int i = static_cast<int>(board->getMinions().size()) - 1; i >= 0; --i) {
        Minion* m = board->getMinions()[i];
        if (m && m->getDefence() <= 0) {
            Minion *removed = board->removeMinion(i + 1);
            if (removed) {
                graveyard->addMinion(removed);
                std::cout << removed->getName() << " has been moved to the graveyard." << std::endl;
            } else {
                std::cerr << "Error: Failed to clean up minion from board." << std::endl;
            }            
        }
    }
}
