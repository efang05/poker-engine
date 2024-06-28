#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"

class Player {
public:
    std::string name;
    std::vector<Card> hand;
    bool inGame;
    double capital;

    Player() : name(""), inGame(true), capital(1000.0) {}
    Player(const std::string& name, double initialCapital) : name(name), inGame(true), capital(initialCapital) {}

    std::string toString() const {
        std::string result = name + ": ";
        for (const auto& card : hand) {
            result += card.toString() + " ";
        }
        return result;
    }
};

#endif // PLAYER_H
