#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>

class GameEngine;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const GameEngine& gameState) = 0;
};

#endif
