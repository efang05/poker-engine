#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <random>
#include "Card.h"

class Deck {
public:
    std::vector<Card> cards;

    Deck() {
        const std::string ranks = "23456789TJQKA";
        const std::string suits = "cdhs";
        for (char r : ranks) {
            for (char s : suits) {
                cards.emplace_back(std::string(1, r) + s);
            }
        }
        shuffle();
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card dealCard() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

#endif // DECK_H
