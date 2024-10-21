#ifndef MCCFR_H
#define MCCFR_H

#include "Game.h"
#include <unordered_map>
#include <random>
#include <ofstream>

class MCCFRNode {
public:
    std::unordered_map<std::string, double> regrets;
    std::unordered_map<std::string, double> strategy;
    std::unordered_map<std::string, double> strategySum;
    int visitCount;

    MCCFRNode() : visitCount(0) {}
};

class MCCFR {
private:
    std::unordered_map<std::string, MCCFRNode> nodes;
    std::mt19937 rng;
    std::ofstream logFile;

    void updateStrategy(MCCFRNode& node);
    double calculateUtility(const Game& game, const Player& player);
    double cfr(Game& game, Player& player, double pi1, double pi2, int depth);
    std::string getStateKey(const Game& game, const Player& player, int handSize);

public:
    MCCFR();
    ~MCCFR();
    void train(Game& game, int iterations);
    Action getAction(const Game& game, const Player& player);
};

#endif // MCCFR_H
