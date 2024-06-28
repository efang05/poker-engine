#include "Game.h"

Player& Game::getOpponent(const Player& player) const {
    if (player.name == player1.name) {
        return const_cast<Player&>(player2);
    } else {
        return const_cast<Player&>(player1);
    }
}

std::vector<Player> Game::getPlayers() const {
    return {player1, player2};
}
