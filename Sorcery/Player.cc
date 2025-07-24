#include "Player.h"
#include "Spell.h"
#include "BuffEffect.h"
#include "SummonEffect.h"
#include <utility>
#include <iostream>

/* Ctor and Dtor */

Player::Player(const std::string &name, const std::string& deckFile, GameEngine* game)
    : name{name}, life{20}, magic{3}, ritual{nullptr}, game{game} {
    deck.load_deck(deckFile);
    if (!game) {
        std::cerr << "Error: GameEngine pointer is null." << std::endl;
        throw std::invalid_argument("GameEngine pointer cannot be null");
    }
    if (!game->isTestingMode()) {
        deck.shuffle();
    }
    for (int i = 0; i < 5; ++i) {
        drawCard();
    }
}

Player::~Player() {}

std::string Player::getName() const { return name; }
int Player::getLife() const { return life; }
int Player::getMagic() const { return magic; }
Ritual* Player::getRitual() const { return ritual.get(); }
const Graveyard* Player::getGraveyard() const { return graveyard; }
Board& Player::getBoard() const { return board; }
Hand& Player::getHand() const { return hand; }

// for testing
void Player::setLife(int l) { life = l; }
void Player::setMagic(int m) { magic = m; }

void Player::takeDamage(int amount) { life -= amount; }
void Player::gainMagic(int amount) { magic += amount; }
void Player::spendMagic(int cost) { magic -= cost; }


void Player::startTurn() {
    gainMagic(1);
    drawCard();
    if (getRitual()) {
        getRitual()->trigger("Start of Turn", this);
    }
}

void Player::endTurn() {
    // TODO: trigger any “end of turn” ritual or minion triggers
}

void Player::playCard(int idx) {
    if (idx < 1 || idx > hand.getSize()) {
        std::cerr << "Error: Invalid card index." << std::endl;
        return;
    }
    Card *c = hand.getCard(idx);
    if (!c) {
        std::cerr << "Error: Invalid card index or Hand is empty" << std::endl;
        return;
    }
    if (c->getCost() > magic) {
        std::cerr << "Error: Not enough magic to play this card." << std::endl;
        return;
    }
    // attempt to play the card
    bool playSuccessful = false;

    // Check if the card is a Ritual
    if (Ritual* ritualCard = dynamic_cast<Ritual*>(c)) {
        if (ritual) {
            std::cout << "Replacing existing ritual: " << ritual->getName() << std::endl;
            ritual.reset();
        }

        ritualCard->play(this); 
        hand.removeCard(idx);
        spendMagic(c->getCost());
        playSuccessful = true;
    }

    // Check if the card is a Minion
    else if (Minion* minionCard = dynamic_cast<Minion*>(c)) {
        if (board.addMinion(minionCard)) {
            Card *toPlay = hand.removeCard(idx); 
            playSuccessful = true;
        } else {
            std::cerr << "Error: Board is full, cannot add minion." << std::endl;
            return;
        }
    }

    // Check if its a spell card
    else if (Spell* spellCard = dynamic_cast<Spell*>(c)) {
        Effect* effect = spellCard->getEffect();

        // Check if it's an enchantment
        if (BuffEffect* buff = dynamic_cast<BuffEffect*>(effect)) {
            Minion* targetMinion = nullptr;  
            
            // TODO:
            // Define how target is selected
            //

            if (!targetMinion) {
                std::cerr << "Error: No valid target selected for enchantment." << std::endl;
                return;
            }

            // Apply the buff
            buff->setTarget(targetMinion);
            buff->apply();

            // Record the spell card on the minion
            targetMinion->addEnchantmentCard(c->clone());

            // Remove spell from hand
            Card* toPlay = hand.removeCard(idx);
            playSuccessful = true;

            std::cout << "Applied enchantment spell: " << c->getName() << " to " << targetMinion->getName() << std::endl;
        } 
        // else
        else {

        }
    }



    // TODO: Handle other card types (Spells, Enchantments, etc.)

    if (playSuccessful) {
        spendMagic(c->getCost());
        c->play();
    } else {
        std::cerr << "Error: Failed to play card." << std::endl;
        return;
    }
}


void Player::playCard(int idx, Player* target, char cardType) {
    if (idx < 1 || idx > hand.getSize()) {
        std::cerr << "Error: Invalid card index." << std::endl;
        return;
    }
    Card* c = hand.getCard(idx);
    if (!c) {
        std::cerr << "Error: Invalid card index or Hand is empty" << std::endl;
        return;
    }
    if (c->getCost() > magic) {
        std::cerr << "Error: Not enough magic to play this card." << std::endl;
        return;
    }

    // TODO: Implement cards that take in target

}

void Player::attack(int fromIdx, int toIdx) {
    if (fromIdx < 1 || fromIdx > board.getMinions().size()) {
        std::cerr << "Error: Invalid attacker Index" << std::endl;
        return;
    }

    Minion* attacker = board.getMinions()[fromIdx - 1];
    if (!attacker) {
        std::cerr << "Error: No minion at attacking index" << std::endl;
        return;
    }

    Player* opponent = game->getInactivePlayer();

    if (toIdx == 0) {
        // attack opposing player
        // TODO: implement in GameEngine context
        if (opponent) {
            attacker->attackPlayer(opponent);
        }
    } else {
        // attack opposing minon
        // TODO: look up opposing player's board and resolve combat
    }
}

void Player::useAbility(int fromIdx, int targetIdx) {
    if (fromIdx < 1 || fromIdx > board.getMinions().size()) {
        std::cerr << "Error: Invalid attacking minion index" << std::endl;
        return;
    }
    Minion* minion = board.getMinions()[fromIdx - 1];
    // Todo: implement m->activateAbility(target)

    if (minion->getAbility()->getEffect()->supportsTarget()) {
        // the ability needs a target
        if (targetIdx < 1 || targetIdx > board.getMinions().size()) {
            std::cerr << "Error: Invalid target index" << std::endl;
            return;
        }
        Board opponentBoard = game->getInactivePlayer()->getBoard();
        Minion* targetMinion = opponentBoard.getMinions()[targetIdx - 1];
        if (!targetMinion) {
            std::cerr << "Error: No minion at target index" << std::endl;
            return;
        }
        minion->useAbility(targetMinion, nullptr);
    }
    // another if to check if its a summon effect
    // if it is supply board
    else if (auto* summonEffect = dynamic_cast<SummonEffect*>(minion->getAbility()->getEffect())) {
        minion->useAbility(nullptr, &board);
    } else {
        // no target needed, just use the ability
        minion->useAbility();
    }
}

void Player::drawCard() {
    if (!hand.isFull() && !deck.isEmpty()) {
        Card* c = deck.draw();
        if (c) {
            hand.addCard(c);
        } else {
            std::cerr << "Error: Failed to draw card from deck." << std::endl;
        }
    }
}

void Player::setRitual(std::unique_ptr<Ritual> newRitual) {
    ritual = std::move(newRitual);
}
