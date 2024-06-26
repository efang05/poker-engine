#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    std::string rank;
    std::string suit;

    Card(std::string r, std::string s) : rank(r), suit(s) {}

    std::string toString() const {
        return rank + suit;
    }
};

#endif // CARD_H
