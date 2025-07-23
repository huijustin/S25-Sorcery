#pragma once
#include <string>

class Observer {
public:
    virtual void update(std::string gameState) = 0;
};
