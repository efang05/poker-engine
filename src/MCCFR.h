#ifndef MCCFR_H
#define MCCFR_H

#include <unordered_map>
#include <random>
#include <fstream>
#include "Game.h"
#include "Player.h"
#include "Strategy.h"
#include "MCCFRNode.h"

class MCCFR {
public:
    MCCFR();
    ~MCCFR();
    void train(Game& game, int iterations);
    Action getAction(const Game& game, const Player& player);
    double calculateUtility(const Game& game, const Player& player);

private:
    std::unordered_map<std::string, MCCFRNode> nodes;
    std::mt19937 rng;
    std::ofstream logFile;

    std::string getStateKey(const Game& game, const Player& player);
    void updateStrategy(MCCFRNode& node);
    double cfr(Game& game, Player& player, double pi1, double pi2, int depth);
};

#endif // MCCFR_H
