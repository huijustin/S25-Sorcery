#pragma once

class Minion;  // forward-declared to avoid cyclic dependency

class Effect {
public:
    virtual ~Effect() = default;

    virtual void apply() = 0;
    virtual bool supportsTarget() const { return false; }
    virtual void setTarget(Minion* target) {}
};
