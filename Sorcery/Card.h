#pragma once
#include <string>

class Card {
protected:
    int cost;
    int cardID;
    std::string name;
    std::string cardText;

public:
    Card(int ID, std::string name, int cost);         
    virtual int getCost();   
    virtual int getID();
    virtual std::string getName() const;
    std::string Card::getCardText() const;
    virtual void play() = 0;
    virtual ~Card();
};
