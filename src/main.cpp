#include "Evaluator.h"
#include "Game.h"
#include "MCCFR.h"
#include <iostream>

int main() {
    const char * path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";

    if (!loadHandRanks(path)) {
        std::cerr << "Failed to load HandRanks.dat file\n";
        return 1;
    }

    Player player1("Alice", 1000.0);
    Player player2("Bob", 1000.0);

    Game game(player1, player2);
    MCCFR mccfr;

    game.dealHands();  // Deal initial hands to players
    game.dealFlop();   // Deal the flop
    game.dealTurn();   // Deal the turn
    game.dealRiver();  // Deal the river

    mccfr.train(game, 10);  // Train with 10 iterations using 4 threads for testing

    for (const auto& player : game.getPlayers()) {
        std::cout << player.name << "'s hand: ";
        for (const auto& card : player.hand) {
            std::cout << card.toString() << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Community cards: ";
    for (const auto& card : game.communityCards) {
        std::cout << card.toString() << " ";
    }
    std::cout << "\n";

    for (auto& player : game.getPlayers()) {
        if (player.inGame) {
            Action action = mccfr.getAction(game, player);
            switch (action) {
                case FOLD:
                    std::cout << player.name << " folds.\n";
                    player.inGame = false;
                    break;
                case CALL:
                    std::cout << player.name << " calls.\n";
                    break;
                case RAISE:
                    std::cout << player.name << " raises.\n";
                    break;
                case CHECK:
                    std::cout << player.name << " checks.\n";
                    break;
            }
        }
    }

    return 0;
}
