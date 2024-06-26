#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include <vector>
#include <string>

class Game {
private:
    Deck deck;
    std::vector<Player> players;
    int pot;

public:
    Game(const std::vector<std::string>& playerNames, int startingChips);
    void startNewRound();
    void dealHands(int cardsPerPlayer);
    void addToPot(int amount);
    int getPot() const;
    const std::vector<Player>& getPlayers() const;
};

#endif // GAME_H
