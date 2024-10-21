#ifndef HAND_HPP
#define HAND_HPP

#include "Rank.hpp"
#include "Suit.hpp"
#include <vector>
#include <string>

struct Card {
    Rank rank;
    Suit suit;

    std::string toString() const {
        const std::string rankStrings[] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
        const std::string suitStrings[] = {"h", "d", "c", "s"};
        return rankStrings[static_cast<int>(rank)] + suitStrings[static_cast<int>(suit)];
    }
};

struct Hand {
    std::vector<Card> cards;

    std::string toString() const {
        std::string handString;
        for (const auto& card : cards) {
            handString += card.toString() + " ";
        }
        return handString;
    }
};

#endif
