#include "GraphicsView.h"
#include "Hand.h"
#include "Board.h"
#include "Ritual.h"
#include "Graveyard.h
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
    window->drawString(10, 20, "Player 1: " + p1->getName());
    window->drawString(10, 40, "Life: " + std::to_string(p1->getLife()) +
                         " Magic: " + std::to_string(p1->getMagic()));

    window->drawString(10, window->getHeight() - 40,
                       "Player 2: " + p2->getName());
    window->drawString(10, window->getHeight() - 20,
                       "Life: " + std::to_string(p2->getLife()) +
                       " Magic: " + std::to_string(p2->getMagic()));
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

// Inspect minion

