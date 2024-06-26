#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <string>

class Player {
public:
    std::string name;
    std::vector<Card> hand;
    int chips;
    bool inGame;

    Player(std::string n, int c) : name(n), chips(c), inGame(true) {}

    void addCardToHand(const Card& card);
    void resetHand();
};

#endif // PLAYER_H
