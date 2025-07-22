#pragma once
#include <string>

class Card {
protected:
    int cost;
    int cardID;
    std::string name;

public:
    Card(int ID, std::string name, int cost);         
    virtual int getCost();   
    virtual int getID();
    virtual std::string getName();
    virtual void play() = 0;
    virtual ~Card();
};
