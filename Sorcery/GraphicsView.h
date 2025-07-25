#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include "GameEngine.h"
#include "Player.h"
#include "Card.h"
#include "Minion.h"
#include "Ritual.h"
#include "Enchantment.h"
#include "Window.h"
#include "Observer.h"
#include <vector>
#include <string>

class GraphicsView : public Observer {
    GameEngine* game;
    Xwindow* window;

public:
    GraphicsView(GameEngine* game);
    ~GraphicsView();

    void notify() override;

    void drawBoard() const;
    void drawHand(int playerIdx) const;
    void inspectMinion(int playerIdx, int minionIdx) const;
};

#endif