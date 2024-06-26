#include "PokerEvaluator.h"
#include "Game.h"
#include "Strategy.h"

int main() {
    const char * path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";

    if (!loadHandRanks(path)) {
        std::cerr << "Failed to load HandRanks.dat file\n";
        return 1;
    }

    std::vector<std::string> playerNames = {"Alice", "Bob", "Charlie"};
    Game game(playerNames, 1000);
    Strategy strategy;

    game.startNewRound();
    game.dealHands(2);  // Deal 2 cards to each player (Texas Hold'em)

    for (const auto& player : game.getPlayers()) {
        std::cout << player.name << "'s hand: ";
        for (const auto& card : player.hand) {
            std::cout << card.toString() << " ";
        }
        std::cout << "\n";
    }

    // Placeholder for the game loop
    for (auto& player : game.getPlayers()) {
        if (player.inGame) {
            Action action = strategy.decideAction(player, game);
            switch (action) {
                case FOLD:
                    player.inGame = false;
                    break;
                case CALL:
                    // Add logic for calling
                    break;
                case RAISE:
                    // Add logic for raising
                    break;
                case CHECK:
                    // Add logic for checking
                    break;
            }
        }
    }

    return 0;
}
