#pragma once
#include "Effect.h"
#include "Minion.h"
#include "Board.h"
#include <memory>

class SummonEffect : public Effect {
    Minion* toSummon;
    int amount;
    Board* summonLocation;

public:
    SummonEffect(Minion* toSummon, int amount, Board* summonLocation);

    void setBoard(Board* board);
    void apply() override;
    bool supportsTarget() const override { return false; }
};
