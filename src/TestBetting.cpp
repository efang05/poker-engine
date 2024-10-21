#include "Game/Game.hpp"
#include <cassert>
#include <iostream>

void testBettingSequences() {
    // Load the hand ranks
    const char* path = "/mnt/c/Users/eddie/Documents/Poker Engine/poker-engine/src/HandRanks.dat";
    assert(loadHandRanks(path) && "Error loading hand ranks.");

    Game game(1000); // Each player starts with 1000 chips

    // Test case 1: A calls, B raises, A folds
    game.resetGameState();
    game.handleAction(PlayerAction::CALL, PlayerAction::RAISE);
    game.handleAction(PlayerAction::FOLD, PlayerAction::NONE);
    std::cout << game.getPot() << std::endl;
    assert(game.getPot() == 120 && "Test case 1 failed");
    std::cout << "Test case 1 passed\n";

    // Test case 2: A calls, B raises, A raises
    game.resetGameState();
    game.handleAction(PlayerAction::CALL, PlayerAction::RAISE);
    game.handleAction(PlayerAction::RAISE, PlayerAction::NONE);
    assert(game.getPot() == 200 && "Test case 2 failed");
    std::cout << "Test case 2 passed\n";

    // Test case 3: A calls, B calls
    game.resetGameState();
    game.handleAction(PlayerAction::CALL, PlayerAction::CALL);
    assert(game.getPot() == 40 && "Test case 3 failed");
    std::cout << "Test case 3 passed\n";

    // Test case 4: A calls, B folds
    game.resetGameState();
    game.handleAction(PlayerAction::CALL, PlayerAction::FOLD);
    assert(game.getPot() == 20 && "Test case 4 failed");
    std::cout << "Test case 4 passed\n";

    // Test case 5: A raises, B raises
    game.resetGameState();
    game.handleAction(PlayerAction::RAISE, PlayerAction::RAISE);
    assert(game.getPot() == 200 && "Test case 5 failed");
    std::cout << "Test case 5 passed\n";

    // Test case 6: A raises, B folds
    game.resetGameState();
    game.handleAction(PlayerAction::RAISE, PlayerAction::FOLD);
    assert(game.getPot() == 100 && "Test case 6 failed");
    std::cout << "Test case 6 passed\n";

    // Test case 7: A checks, B raises, A folds
    game.resetGameState();
    game.handleAction(PlayerAction::CHECK, PlayerAction::RAISE);
    game.handleAction(PlayerAction::FOLD, PlayerAction::NONE);
    assert(game.getPot() == 100 && "Test case 7 failed");
    std::cout << "Test case 7 passed\n";

    // Test case 8: A checks, B raises, A raises
    game.resetGameState();
    game.handleAction(PlayerAction::CHECK, PlayerAction::RAISE);
    game.handleAction(PlayerAction::RAISE, PlayerAction::NONE);
    assert(game.getPot() == 200 && "Test case 8 failed");
    std::cout << "Test case 8 passed\n";

    // Test case 9: A checks, B checks
    game.resetGameState();
    game.handleAction(PlayerAction::CHECK, PlayerAction::CHECK);
    assert(game.getPot() == 0 && "Test case 9 failed");
    std::cout << "Test case 9 passed\n";

    // Test case 10: A checks, B calls, A folds
    game.resetGameState();
    game.handleAction(PlayerAction::CHECK, PlayerAction::CALL);
    game.handleAction(PlayerAction::FOLD, PlayerAction::NONE);
    assert(game.getPot() == 20 && "Test case 10 failed");
    std::cout << "Test case 10 passed\n";

    // Test case 11: A checks, B calls, A calls
    game.resetGameState();
    game.handleAction(PlayerAction::CHECK, PlayerAction::CALL);
    game.handleAction(PlayerAction::CALL, PlayerAction::NONE);
    assert(game.getPot() == 20 && "Test case 11 failed");
    std::cout << "Test case 11 passed\n";

    // Test case 12: A checks, B calls, A raises, B folds
    game.resetGameState();
    game.handleAction(PlayerAction::CHECK, PlayerAction::CALL);
    game.handleAction(PlayerAction::RAISE, PlayerAction::FOLD);
    assert(game.getPot() == 100 && "Test case 12 failed");
    std::cout << "Test case 12 passed\n";

    // Test case 13: A checks, B calls, A raises, B raises
    game.resetGameState();
    game.handleAction(PlayerAction::CHECK, PlayerAction::CALL);
    game.handleAction(PlayerAction::RAISE, PlayerAction::RAISE);
    assert(game.getPot() == 200 && "Test case 13 failed");
    std::cout << "Test case 13 passed\n";

    std::cout << "All test cases passed!\n";
}

int main() {
    testBettingSequences();
    return 0;
}
