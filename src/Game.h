#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"

class Game {
public:
    Player player1;
    Player player2;
    Deck deck;
    std::vector<Card> communityCards;
    double potSize;

    Game(const Player& p1, const Player& p2) : player1(p1), player2(p2), potSize(0.0) {}

    Player& getOpponent(const Player& player) const;
    std::vector<Player> getPlayers() const;

    void dealHands() {
        player1.hand = {deck.dealCard(), deck.dealCard()};
        player2.hand = {deck.dealCard(), deck.dealCard()};
    }

    void dealFlop() {
        communityCards = {deck.dealCard(), deck.dealCard(), deck.dealCard()};
    }

    void dealTurn() {
        communityCards.push_back(deck.dealCard());
    }

    void dealRiver() {
        communityCards.push_back(deck.dealCard());
    }

    void resetPot() {
        potSize = 0.0;
    }

    void addToPot(double amount) {
        potSize += amount;
    }
};

#endif // GAME_H
