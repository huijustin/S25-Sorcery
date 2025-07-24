#pragma once
#include <memory>

class Minion;  // forward-declared to avoid cyclic dependency

class Effect {
public:
    virtual ~Effect() = default;

    virtual void apply() = 0;
    virtual bool supportsTarget() const { return false; }
    virtual void setTarget(Minion* target) {}
    virtual std::unique_ptr<Effect> clone() const = 0;

};
