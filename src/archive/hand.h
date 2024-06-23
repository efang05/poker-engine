// Hand.h
#pragma once
#include <vector>
#include "Card.h"

class Hand {
public:
    void addCard(const Card& card);
    const std::vector<Card>& getCards() const;

private:
    std::vector<Card> cards;
};