#pragma once
#include <string>
#include "Minion.h"

class Ability {
public:
    virtual ~Ability() = default;

    virtual void useEffect(Minion* target = nullptr) = 0;  // Optional target
    virtual std::string getDescription() const = 0;
};
