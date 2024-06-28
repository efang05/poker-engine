#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    std::string rank;
    std::string suit;

    Card(const std::string& card) {
        rank = card.substr(0, card.size() - 1);
        suit = card.substr(card.size() - 1);
    }

    Card(std::string r, std::string s) : rank(r), suit(s) {}

    std::string toString() const {
        return rank + suit;
    }
};

#endif // CARD_H
