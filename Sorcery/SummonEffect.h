#pragma once
#include "Effect.h"
#include "Minion.h"
#include <memory>

class Board;

class SummonEffect : public Effect {
    Minion* toSummon;
    int amount;
    Board* summonLocation;

public:
    SummonEffect(Minion* toSummon, int amount, Board* summonLocation);

    void setBoard(Board* board);
    void apply() override;
    bool supportsTarget() const override { return false; }
    virtual std::unique_ptr<Effect> clone() const = 0;

};
