#include "Util/Evaluator.hpp"
#include "Game/Game.hpp"
#include <iostream>

int main() {
    const char* path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";

    if (!loadHandRanks(path)) {
        std::cerr << "Failed to load HandRanks.dat file\n";
        return 1;
    }
}
