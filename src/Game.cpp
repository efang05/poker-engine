#include "Game.h"

Game::Game(const std::vector<std::string>& playerNames, int startingChips) {
    for (const auto& name : playerNames) {
        players.emplace_back(name, startingChips);
    }
    pot = 0;
}

void Game::startNewRound() {
    deck.reset();
    deck.shuffle();
    for (auto& player : players) {
        player.resetHand();
    }
    pot = 0;
}

void Game::dealHands(int cardsPerPlayer) {
    for (int i = 0; i < cardsPerPlayer; ++i) {
        for (auto& player : players) {
            if (player.inGame) {
                player.addCardToHand(deck.dealCard());
            }
        }
    }
}

void Game::addToPot(int amount) {
    pot += amount;
}

int Game::getPot() const {
    return pot;
}

const std::vector<Player>& Game::getPlayers() const {
    return players;
}
