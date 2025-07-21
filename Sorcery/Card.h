#pragma once
class Card {
public:
    virtual int getCost() = 0;
    virtual void play() = 0;
    virtual ~Card() {}
};