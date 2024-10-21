#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Hand.hpp"

struct Player {
    Hand hand;
    int chips;
    bool hasFolded;

    Player(int startingChips);
    void receiveCard(const Card& card);
    void resetHand();
};

#endif
