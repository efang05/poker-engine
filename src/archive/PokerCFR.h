#pragma once
#include "HandEvaluator.h"
#include "GameState.h"
#include "Node.h"
#include <string>
#include <random>
#include <unordered_map>

// PokerCFR.h
class PokerCFR {
public:
    PokerCFR(int iterations);
    void train();
    std::vector<double> getStrategy(const GameState& gameState);
    void saveState(const std::string& filename);
    void loadState(const std::string& filename);

private:
    double cfr(const GameState& gameState, std::vector<int>& history, int traversingPlayer, const std::vector<Hand>& opponents);
    bool isTerminal(const std::vector<int>& history);
    double payoff(const GameState& gameState, const std::vector<int>& history, const std::vector<Hand>& opponents);
    std::string getInfoset(const GameState& gameState, const std::vector<int>& history);
    GameState generateRandomGameState();
    std::vector<Hand> generateOpponentHands(int numOpponents);

    int iterations;
    std::unordered_map<std::string, Node> nodes;
    std::mt19937 rng;
};