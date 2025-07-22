#pragma once

class Effect {
public:
    virtual ~Effect() = default;
    virtual void apply() = 0;
};
