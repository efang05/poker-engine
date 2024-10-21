#include "Game/Game.hpp"
#include <iostream>

int main() {
    // Load the hand ranks
    const char* path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";
    if (!loadHandRanks(path)) {
        std::cerr << "Error loading hand ranks.\n";
        return 1;
    }

    Game game(1000); // Each player starts with 1000 chips

    // Play a single round of the game
    game.playRound();

    return 0;
}
