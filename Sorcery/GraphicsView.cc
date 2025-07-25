#include "GraphicsView.h"
#include "Hand.h"
#include "Board.h"
#include "Ritual.h"
#include "Graveyard.h"
#include "ascii_graphics.h"
#include <iostream>

GraphicsView::GraphicsView(GameEngine* game) : game{game}, window{new Xwindow{800, 600}} {
    game->attach(this);
}

GraphicsView::~GraphicsView() {
    game->detach(this);
    delete window;
}

void GraphicsView::notify() {
    drawBoard();
}

void GraphicsView::drawBoard() const {
    Player *p1 = game->getPlayer(0);
    Player *p2 = game->getPlayer(1);
    if (!p1 || !p2) {
        std::cerr << "Error: Players not found in game." << std::endl;
        return;
    }

    window->fillRectangle(0, 0, window->getWidth(), window->getHeight(), Xwindow::White);

    // player 1 info at the top
    window->drawString(10, 20, "Player 1: " + p1->getName());
    window->drawString(10, 40,
                       "Life: " + std::to_string(p1->getLife()) +
                       "  Magic: " + std::to_string(p1->getMagic()));

    // draw ritual and graveyard for player 1
    int yOffset = 60;
    if (auto r = p1->getRitual()) {
        window->drawString(10, yOffset,
                           "Ritual: " + r->getName() +
                               " (" + std::to_string(r->getCharges()) + ")");
    } else {
        window->drawString(10, yOffset, "Ritual: none");
    }

    auto g1 = p1->getGraveyard()->getTop();
    if (g1) {
        window->drawString(300, yOffset,
                           "Grave: " + g1->getName());
    } else {
        window->drawString(300, yOffset, "Grave: empty");
    }

    // draw minions for player 1
    int x = 10;
    int y = 90;
    const auto &p1Board = p1->getBoard()->getMinions();
    for (int i = 0; i < 5; ++i) {
        std::string msg;
        if (i < static_cast<int>(p1Board.size()) && p1Board[i]) {
            auto m = p1Board[i];
            msg = m->getName() + " " + std::to_string(m->getAttack()) + "/" +
                  std::to_string(m->getDefence());
        } else {
            msg = "(empty)";
        }
        window->drawString(x, y, msg);
        x += 150;
    }

    // centre indicator for whose turn it is
    window->drawString(10, window->getHeight() / 2,
                       "Turn: " + game->getActivePlayer()->getName());

    // draw minions for player 2
    x = 10;
    y = window->getHeight() - 70;
    const auto &p2Board = p2->getBoard()->getMinions();
    for (int i = 0; i < 5; ++i) {
        std::string msg;
        if (i < static_cast<int>(p2Board.size()) && p2Board[i]) {
            auto m = p2Board[i];
            msg = m->getName() + " " + std::to_string(m->getAttack()) + "/" +
                  std::to_string(m->getDefence());
        } else {
            msg = "(empty)";
        }
        window->drawString(x, y, msg);
        x += 150;
    }

    // draw ritual and graveyard for player 2 below minions
    yOffset = window->getHeight() - 50;
    if (auto r = p2->getRitual()) {
        window->drawString(10, yOffset,
                           "Ritual: " + r->getName() +
                               " (" + std::to_string(r->getCharges()) + ")");
    } else {
        window->drawString(10, yOffset, "Ritual: none");
    }

    auto g2 = p2->getGraveyard()->getTop();
    if (g2) {
        window->drawString(300, yOffset,
                           "Grave: " + g2->getName());
    } else {
        window->drawString(300, yOffset, "Grave: empty");
    }

    // player 2 info
    window->drawString(10, window->getHeight() - 20,
                       "Player 2: " + p2->getName());
    window->drawString(10, window->getHeight() - 5,
                       "Life: " + std::to_string(p2->getLife()) +
                       "  Magic: " + std::to_string(p2->getMagic()));
}

void GraphicsView::drawHand(int playerIdx) const {
    Player *player = game->getPlayer(playerIdx);
    if (!player) return;
    int x = 10;
    int y = (playerIdx == 0 ? 70 : window->getHeight() - 70);
    for (Card* card : player->getHand()->getCards()) {
        if (card) {
            window->drawString(x, y, card->getName() + " (" + std::to_string(card->getCost()) + ")");
            x += 100; // Adjust spacing between cards
        } else {
            window->drawString(x, y, "Empty Hand Slot");
            x += 100; // Adjust spacing for empty slots
        }
    }
}

void GraphicsView::inspectMinion(int playerIdx, int minionIdx) const {
    Player *player = game->getPlayer(playerIdx);
    if (!player || minionIdx < 1 || minionIdx > 5) {
        std::cerr << "Error: Invalid player or minion index." << std::endl;
        return;
    }

    const auto &minions = player->getBoard()->getMinions();
    if (minionIdx - 1 >= static_cast<int>(minions.size()) || !minions[minionIdx - 1]) {
        std::cerr << "Error: No minion at index " << minionIdx << std::endl;
        return;
    }

    Minion *m = minions[minionIdx - 1];

    window->fillRectangle(0, 0, window->getWidth(), window->getHeight(), Xwindow::White);
    window->drawString(10, 20, "Minion: " + m->getName());
    window->drawString(10, 40,
                       "Cost: " + std::to_string(m->getCost()) +
                       "  ATK/DEF: " + std::to_string(m->getAttack()) + "/" +
                           std::to_string(m->getDefence()));

    if (auto ab = m->getAbility()) {
        window->drawString(10, 60, "Ability: " + ab->getDescription());
    }

    auto stack = m->getEnchantmentStack();
    int y = 80;
    for (Card *e : stack) {
        window->drawString(10, y, "Enchantment: " + e->getName());
        y += 20;
    }
}

