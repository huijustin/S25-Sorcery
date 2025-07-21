#pragma once
#include "Observer.h"

class TextView : public Observer {
public:
    void update(std::string gameState) override;
};
