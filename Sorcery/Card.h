#pragma once

class Card {
protected:
    int cost;
public:
    Card(int cost);         
    virtual int getCost();   
    virtual void play() = 0;
    virtual ~Card();
};
