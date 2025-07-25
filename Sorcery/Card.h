#pragma once
#include <string>
#include <memory>
#include "ascii_graphics.h"

class Card {
protected:
    int cost;
    int cardID;
    std::string name;
    std::string cardText;

public:
    Card(int ID, std::string name, int cost, std::string cardText);         
    virtual int getCost();   
    virtual int getID();
    virtual std::string getName() const;
    std::string getCardText() const;
    virtual void play() = 0;
    virtual ~Card();
    virtual card_template_t getTemplate() const = 0; // Abstract method for rendering

    virtual std::unique_ptr<Card> clone() const = 0; // Required to clone subclasses
};
