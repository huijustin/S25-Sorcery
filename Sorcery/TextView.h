#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "Observer.h"
#include "GameEngine.h"
#include <iostream>

class TextView : public Observer {
public:
    void update(const GameEngine& gameState) override;
};

#endif
