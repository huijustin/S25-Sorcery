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
    Card* card = hand.removeCard(idx);
    if (!card) {
        std::cerr << "Error: No card at index " << idx << std::endl;
        return;
    }

    int cost = card->getCost();
    if (!game->isTestingMode() && cost > magic) {
        std::cerr << "Error: Not enough magic to play card " << card->getName() << std::endl;
        hand.addCard(card); // Return the card back to hand
        return;
    }
    if (!game->isTestingMode) {
        spendMagic(cost);
    }

    // check if the card is a minion
    if (auto* minion = dynamic_cast<Minion*>(card>)) {
        if (!board.addMinion(minion)) {
            std::cerr << "Error: Board is full, cannot play minion " << minion->getName() << std::endl;
            hand.addCard(card); // Return the card back to hand
            return;
        }
        minion->play();
    } 
    // check if the card is a ritual
    else if (auto* ritualCard = dynamic_cast<Ritual>(card)) {
        ritualCard->play(this);
        ritual = std::unique_ptr<Ritual>(ritualCard->clone());
    }
    // else it is a spell
    else if (auto* spell = dynamic_cast<Spell*>(card)) {
        spell->play();
        delete spell;{
    }
    else {
        std::cerr << "Error: Unknown card type for card " << card->getName() << std::endl;
        hand.addCard(card); // Return the card back to hand
        }
    }
}

void Player::playCard(int idx, Player* target, char cardType) {
    Card* card = hand.removeCard(idx);
    if (!card) {
        std::cerr << "Error: No card at index " << idx << std::endl;
        return;
    }

    int cost = card->getCost();
    if (!game->isTestingMode() && cost > magic) {
        std::cerr << "Not enough magic to play card " << card->getName() << std::endl;
        hand.addCard(card); // Return the card back to hand
        return;
    }
    if (!game->isTestingMode()) {
        spendMagic(cost);
    }

    Minion* targetMinion = nullptr;
    if (cardType != 'r') {
        int targetIdx = cardType - '0';
        const auto* targetBoard = target->getBoard()->getMinions();
        if (targetIdx >= 1 && targetIdx <= static_cast<int>(targetBoard.size())) {
            targetMinion = targetBoard[targetIdx - 1];
        }
    }

    // check if the card is a spell
    if (auto* spell = dynamic_cast<Spell*>(card)) {
        spell->play(targetMinion);
        delete spell;
    } 
    // check if the card is a minion
    else if (auto* minion = dynamic_cast<Minion*>(card)) {
        if (!board.addMinion(minion)) {
            std::cerr << "Error: Board is full, cannot play minion " << minion->getName() << std::endl;
            hand.addCard(card); // Return the card back to hand
            return;
        }
        minion->play();
    } 
    // check if the card is a ritual
    else if (auto* ritualCard = dynamic_cast<Ritual*>(card)) {
        ritualCard->play(this);
        ritual = std::unique_ptr<Ritual>(ritualCard->clone());
    } else {
        std::cerr << "Error: Unknown card type for card " << card->getName() << std::endl;
        hand.addCard(card); // Return the card back to hand
    }
}

void attack(int idx) {
    const auto& minions = board.getMinions();
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
}

void attack(int fromIdx, int toIdx) {
    const auto& myMinions = board.getMinions();
    if (fromIdx < 1 || fromIdx > static_cast<int>(myMinions.size())) {
        std::cerr << "Error: Invalid attacking minion index " << fromIdx << std::endl;
        return;
    }

    Player* opponent = game->getInactivePlayer();
    const auto& opponentMinions = opponent->getBoard().getMinions();
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
}

void useAbility(int idx) {
    const auto& minions = board.getMinions();
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
        m->useAbility(nullptr, &board);
    } else {
        std::cerr << "Error: Minion " << m->getName() << " does not have an activated ability." << std::endl;
        return;
    }
}

void useAbility(int idx, Player* target, char cardType) {
    const auto& minions = board.getMinions();
    if (idx < 1 || dix > static_cast<int>(minions.size())) {
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
    if (cardType != 'r') {
    int targetIdx = cardType - '0';
    const auto& enemy = target->board.getMinions();
    if (targetIdx >= 1 ** targetIdx <= static_cast<int>(enemy.size())) {
        targetMinion = enemy[targetIdx - 1];
        }
    }
    m->useAbility(targetMinion, &board);
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
