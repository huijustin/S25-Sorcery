#include "TextView.h"
#include "Card.h"
#include <algorithm>

// helper function to print a row of cards sid by side
void printCardRow(const std::vector<card_template_t>& cards) {
    if (cards.empty()) return;

    size_t numLines = cards[0].size();
    for (size_t i = 0; i < numLines; ++i) {
        for (const auto& card : cards) {
            if (i < card.size()) {
                std::cout << card[i];
            }
        }
        std::cout << std::endl;
    }
}

TextView::TextView(GameEngine* game) : game{game} {
    game->attach(this);
}

TextView::~TextView() {
    game->detach(this);
}

void TextView::printBoard() const {
    Player *p1 = game->getPlayer(0);
    Player *p2 = game->getPlayer(1);

    if (!p1 || !p2) {
        std::cerr << "Error: Players not found in game." << std::endl;
        return;
    }

    // Top border of game board
    const std::string border_h = std::string(185, EXTERNAL_BORDER_CHAR_LEFT_RIGHT[0]);
    std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT << border_h << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

    // Player 1 Top row (ritual, player card, graveyard)
    std::vector<card_template_t> p1_topRow;
    p1_topRow.push_back(p1->getRitual() ? p1->getRitual()->getTemplate() : CARD_TEMPLATE_BORDER);
    p1_topRow.push_back(CARD_TEMPLATE_EMPTY);
    p1_topRow.push_back(display_player_card(1, p1->getName(), p1->getLife(), p1->getMagic()));
    p1_topRow.push_back(CARD_TEMPLATE_EMPTY);
    p1_topRow.push_back(p1->getGraveyard()->isEmpty() ? CARD_TEMPLATE_BORDER : p1->getGraveyard()->getTop()->getTemplate());
    printCardRow(p1_topRow);

    // Player 1 Minions
    std::vector<card_template_t> p1_minions;
    for (int i = 0; i < 5; ++i) {
        p1_minions.push_back(p1->getBoard()->getMinions()[i] ? p1->getBoard()->getMinions()[i]->getTemplate() : CARD_TEMPLATE_BORDER);
    }
    printCardRow(p1_minions);

    // Center graphic
    for (const auto& line : CENTRE_GRAPHIC) {
        std::cout << line << std::endl;
    }

    // Player 2 Minions
    std::vector<card_template_t> p2_minions;
    for (int i = 0; i < 5; ++i) {
        p2_minions.push_back(p2->getBoard()->getMinions()[i] ? p2->getBoard()->getMinions()[i]->getTemplate() : CARD_TEMPLATE_BORDER);
    }
    printCardRow(p2_minions);

    // Player 2 bottom row (ritual, player card, graveyard)
    std::vector<card_template_t> p2_bottomRow;
    p2_bottomRow.push_back(p2->getRitual() ? p2->getRitual()->getTemplate() :CARD_TEMPLATE_BORDER);
    p2_bottomRow.push_back(CARD_TEMPLATE_EMPTY);
    p2_bottomRow.push_back(display_player_card(1,p2->getName(), p2->getLife(), p2->getMagic()));
    p2_bottomRow.push_back(CARD_TEMPLATE_EMPTY);
    p2_bottomRow.push_back(p2->getGraveyard()->isEmpty() ? CARD_TEMPLATE_BORDER : p2->getGraveyard()->getTop()->getTemplate());
    printCardRow(p2_bottomRow);

    // Bottom border of game board
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT << border_h << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

void TextView::printHand(int playerIdx) const {
    Player *player = game->getPlayer(playerIdx);
    if (!player) {
        std::cerr << "Error: Invalid player, cannot print hand" << std::endl;
        return;
    }
    const auto& hand = player->getHand()->getCards();
    std::vector<card_template_t> handTemplates;
    for (const auto& card : hand) {
        handTemplates.push_back(card->getTemplate());
    }
    printCardRow(handTemplates);
}

void TextView::inspectMinion(int playerIdx, int minionIdx) const {
    Player* player = game->getPlayer(playerIdx);
    if (!player || minionIdx < 1 || minionIdx > 5) {
        std::cerr << "Error: Invalid player or minion index." << std::endl;
        return;
    }

    const auto& minion = player->getBoard()->getMinions()[minionIdx - 1];
    if (!minion) {
        std::cerr << "Error: No minion at index " << minionIdx << std::endl;
        return;
    }
    printCardRow({minion->getTemplate()});

    // Collect enchantments from base to top
    std::vector<Card*> enchantmentStack = minion->getEnchantmentStack();

    // Print each enchantment in rows of 5
    for (size_t i = 0; i < enchantmentStack.size(); i += 5) {
        std::vector<card_template_t> row;
        for (size_t j = i; j < i + 5 && j < enchantmentStack.size(); ++j) {
            row.push_back(enchantmentStack[j]->getTemplate());
        }
        printCardRow(row);
    }
}

void TextView::notify() {
    printBoard();
}
 