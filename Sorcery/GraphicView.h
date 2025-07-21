#pragma once
#include "Observer.h"

class GraphicView : public Observer {
public:
    void update(std::string gameState) override;
};