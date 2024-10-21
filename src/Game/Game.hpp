#ifndef GAME_HPP
#define GAME_HPP

#include "../Base/Hand.hpp"
#include "../Base/Player.hpp"
#include "../Base/Deck.hpp"
#include "../Util/Evaluator.hpp"
#include "Action.hpp"
#include "HandHistory.hpp"
#include "BettingState.hpp"
#include <vector>
#include <string>

class Game {
public:
    Game(int startingChips);
    void playRound();
    void resetGameState();
    int getPot() const;
    void handleAction(PlayerAction action1, PlayerAction action2);

private:
    HandHistory history;
    Player player1;
    Player player2;
    int pot;
    Deck deck;
    std::vector<Card> communityCards;

    void setupRound();
    void dealHands();
    void dealFlop();
    void dealTurn();
    void dealRiver();
    void printGameState(bool showHands = false);
    void bettingRound(PlayerAction action1, PlayerAction action2, bool isFinalRound = false);
    void determineWinner();
    void addHistory(const std::string& action);

    std::vector<std::string> getCurrentGameState() const;
};

#endif