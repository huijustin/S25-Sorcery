#include "SummonEffect.h"
#include "Board.h"
#include <iostream>

SummonEffect::SummonEffect(Minion* toSummon, int amount, Board* summonLocation)
    : toSummon(toSummon), amount(amount), summonLocation(summonLocation) {}

void SummonEffect::apply() {
    if (!summonLocation || !toSummon) {
        std::cerr << "Summon Error: Missing board or minion pointer" << std::endl;
        return;
    }

    for (int i = 0; i < amount; ++i) {
        std::unique_ptr<Minion> newMinion(
            static_cast<Minion*>(toSummon->clone().release())
        );

        // if fail to summon then break
        if (!summonLocation->addMinion(newMinion.get())) {
            break;
        }

        newMinion.release();  // prevent destructor from deleting it
    }

    std::cout << "Summoned " << amount << " " << toSummon->getName() << "(s) to the board." << std::endl;
}

void SummonEffect::setBoard(Board* board) {
    summonLocation = board;
}

std::unique_ptr<Effect> SummonEffect::clone() const {
    return std::make_unique<SummonEffect>(toSummon ? toSummon->cloneMinion().release() : nullptr,amount,summonLocation );
}
