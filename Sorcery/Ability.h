#pragma once
#include <memory>
#include "Effect.h"
#include "Minion.h"

class Ability {
protected:
    std::unique_ptr<Effect> effect;
    std::string description;

public:
    Ability(std::unique_ptr<Effect> effect, std::string description);
    virtual ~Ability() = default;

    virtual void useEffect(class Minion* target = nullptr) = 0;
    Effect* getEffect() const;
    std::string getDescription() const;

    virtual std::unique_ptr<Ability> clone() const = 0;
};
