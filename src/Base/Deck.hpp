#ifndef DECK_HPP
#define DECK_HPP

#include "Hand.hpp"
#include <vector>

class Deck {
public:
    Deck();
    void shuffle();
    Card dealCard();

private:
    std::vector<Card> cards;
};

#endif