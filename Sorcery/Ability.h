#pragma once
#include <string>

// Abstract
class Ability {
public:
    virtual ~Ability() = default;

    virtual void useEffect() = 0;
    virtual std::string getDescription() const = 0;
};
