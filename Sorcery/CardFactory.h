#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Card.h"

class CardFactory {
    std::vector<std::unique_ptr<Card>> masterList;

public:
    CardFactory();
    ~CardFactory();

    const std::vector<std::unique_ptr<Card>>& getMasterList() const;

    std::unique_ptr<Card> cloneCardByID(int id) const;
    std::unique_ptr<Card> cloneCardByName(const std::string& name) const;
};
