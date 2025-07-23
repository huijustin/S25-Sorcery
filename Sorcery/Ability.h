#pragma once
#include <memory>
#include "Effect.h"
#include "Minion.h"

class Ability {
protected:
    std::unique_ptr<Effect> effect;
    std::string description;

public:
    Ability(std::unique_ptr<Effect> effect);
    virtual ~Ability() = default;

    virtual void useEffect(class Minion* target = nullptr) = 0;

    Effect* getEffect() const;
    std::string getDescription() const;
};
