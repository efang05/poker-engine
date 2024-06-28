#include "Evaluator.h"
#include "Game.h"
#include "MCCFR.h"
#include <iostream>

int main() {
    const char *path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";

    if (!loadHandRanks(path)) {
        std::cerr << "Failed to load HandRanks.dat file\n";
        return 1;
    }

    Player player1("Alice", 1000.0);
    Player player2("Bob", 1000.0);

    Game game(player1, player2);
    MCCFR mccfr;

    mccfr.train(game, 10);  // Train with 10 iterations

    game.resetPot();
    game.dealHands();  // Deal initial hands to players

    for (const auto& player : game.getPlayers()) {
        std::cout << player.name << "'s hand: ";
        for (const auto& card : player.hand) {
            std::cout << card.toString() << " ";
        }
        std::cout << "\n";
    }

    // Flop
    game.dealFlop();
    std::cout << "Community cards: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << game.communityCards[i].toString() << " ";
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
                    game.addToPot(10);
                    player.capital -= 10;
                    break;
                case RAISE:
                    std::cout << player.name << " raises.\n";
                    game.addToPot(20);
                    player.capital -= 20;
                    break;
                case CHECK:
                    std::cout << player.name << " checks.\n";
                    break;
            }
        }
    }

    // Turn
    game.dealTurn();
    std::cout << "Community cards: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << game.communityCards[i].toString() << " ";
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
                    game.addToPot(10);
                    player.capital -= 10;
                    break;
                case RAISE:
                    std::cout << player.name << " raises.\n";
                    game.addToPot(20);
                    player.capital -= 20;
                    break;
                case CHECK:
                    std::cout << player.name << " checks.\n";
                    break;
            }
        }
    }

    // River
    game.dealRiver();
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
                    game.addToPot(10);
                    player.capital -= 10;
                    break;
                case RAISE:
                    std::cout << player.name << " raises.\n";
                    game.addToPot(20);
                    player.capital -= 20;
                    break;
                case CHECK:
                    std::cout << player.name << " checks.\n";
                    break;
            }
        }
    }

    // Determine the winner
    double aliceUtility = mccfr.calculateUtility(game, game.getPlayers()[0]);
    double bobUtility = mccfr.calculateUtility(game, game.getPlayers()[1]);
    if (aliceUtility > bobUtility) {
        std::cout << "Alice wins.\n";
    } else if (bobUtility > aliceUtility) {
        std::cout << "Bob wins.\n";
    } else {
        std::cout << "It's a tie.\n";
    }

    return 0;
}
