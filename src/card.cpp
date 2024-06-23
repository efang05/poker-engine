#include "Card.h"

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

std::string Card::toString() const {
    static const std::string rankStrings[] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
    static const std::string suitStrings[] = {"C", "D", "H", "S"};
    return rankStrings[rank - 2] + suitStrings[suit];
}

Card::Rank Card::getRank() const { return rank; }
Card::Suit Card::getSuit() const { return suit; }