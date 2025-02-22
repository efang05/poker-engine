#include "MCCFR.h"
#include "Evaluator.h"
#include "Game.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>

// Constructor: Initialize the log file
MCCFR::MCCFR() : rng(std::random_device{}()) {
    logFile.open("mccfr_log.txt", std::ios::out);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file" << std::endl;
        exit(1);
    }
}

// Destructor: Close the log file
MCCFR::~MCCFR() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string MCCFR::getStateKey(const Game& game, const Player& player, int handSize) {
    std::vector<std::string> handStrings;
    for (const auto& card : player.hand) {
        handStrings.push_back(card.toString());
    }
    for (const auto& card : game.getCommunityCards()) {
        handStrings.push_back(card.toString());
    }
    return encodeState(handStrings, handSize);
}


void MCCFR::updateStrategy(MCCFRNode& node) {
    double normalizingSum = 0;
    for (const auto& [action, regret] : node.regrets) {
        node.strategy[action] = std::max(0.0, regret);
        normalizingSum += node.strategy[action];
    }
    for (auto& [action, probability] : node.strategy) {
        if (normalizingSum > 0) {
            probability /= normalizingSum;
        } else {
            probability = 1.0 / node.strategy.size();
        }
        node.strategySum[action] += probability;
    }
}

double MCCFR::calculateUtility(const Game& game, const Player& player) {
    const Player& opponent = game.getOpponent(player);

    std::vector<std::string> playerHand;
    for (const auto& card : player.hand) {
        playerHand.push_back(card.toString());
    }
    for (const auto& card : game.getCommunityCards()) {
        playerHand.push_back(card.toString());
    }

    std::vector<std::string> opponentHand;
    for (const auto& card : opponent.hand) {
        opponentHand.push_back(card.toString());
    }
    for (const auto& card : game.getCommunityCards()) {
        opponentHand.push_back(card.toString());
    }

    HandResult playerResult = evalHand(playerHand);
    HandResult opponentResult = evalHand(opponentHand);

    if (playerResult.value > opponentResult.value) {
        return game.getPotSize(); // Player wins
    } else if (playerResult.value < opponentResult.value) {
        return -game.getPotSize(); // Opponent wins
    } else {
        return 0.0; // Tie
    }
}

double MCCFR::cfr(Game& game, Player& player, double pi1, double pi2, int depth, int handSize) {
    if (depth > 10 || !player.inGame) return 0;

    std::string stateKey = getStateKey(game, player, handSize);
    MCCFRNode& node = nodes[stateKey];

    if (node.visitCount == 0) {
        // Initialize node if visiting for the first time
        node.regrets = {{"FOLD", 0}, {"CALL", 0}, {"RAISE", 0}, {"CHECK", 0}};
        node.strategy = {{"FOLD", 1.0 / 4}, {"CALL", 1.0 / 4}, {"RAISE", 1.0 / 4}, {"CHECK", 1.0 / 4}};
        node.strategySum = {{"FOLD", 0}, {"CALL", 0}, {"RAISE", 0}, {"CHECK", 0}};
        node.visitCount = 0;
    }
    updateStrategy(node);

    // Log the current state and action probabilities
    logFile << "Depth: " << depth << ", State: " << stateKey << ", Strategies: ";
    for (const auto& [action, probability] : node.strategy) {
        logFile << action << "=" << probability << " ";
    }
    logFile << std::endl;

    // Select an action based on the current strategy
    std::vector<std::string> actions = {"FOLD", "CALL", "RAISE", "CHECK"};
    std::discrete_distribution<> dist({node.strategy["FOLD"], node.strategy["CALL"], node.strategy["RAISE"], node.strategy["CHECK"]});
    std::string action = actions[dist(rng)];

    double piAction = node.strategy[action];
    std::unordered_map<std::string, double> actionUtilities;

    // Calculate the utility of each action
    for (const auto& a : actions) {
        Player actionPlayer = player;
        Game actionGame = game;

        logFile << "Depth: " << depth << ", Action: " << a << std::endl;

        if (a == "FOLD") {
            actionPlayer.inGame = false;
            actionUtilities[a] = -game.getPotSize(); // Assume fold has negative utility equal to the pot size
        } else if (a == "CALL") {
            if (actionPlayer.capital < 10) {
                actionPlayer.inGame = false;
                actionUtilities[a] = -game.getPotSize();
            } else {
                actionGame.addToPot(10);
                actionPlayer.capital -= 10;
                logFile << "Depth: " << depth << ", Action: " << a << ", Before cfr, Pot Size: " << actionGame.getPotSize() << ", Player Capital: " << actionPlayer.capital << std::endl;
                actionUtilities[a] = cfr(actionGame, actionPlayer, pi1 * piAction, pi2, depth + 1, handSize);
                logFile << "Depth: " << depth << ", Action: " << a << ", After cfr, Utility: " << actionUtilities[a] << std::endl;
            }
        } else if (a == "RAISE") {
            if (actionPlayer.capital < 20) {
                actionPlayer.inGame = false;
                actionUtilities[a] = -game.getPotSize();
            } else {
                actionGame.addToPot(20);
                actionPlayer.capital -= 20;
                logFile << "Depth: " << depth << ", Action: " << a << ", Before cfr, Pot Size: " << actionGame.getPotSize() << ", Player Capital: " << actionPlayer.capital << std::endl;
                actionUtilities[a] = cfr(actionGame, actionPlayer, pi1 * piAction, pi2, depth + 1, handSize);
                logFile << "Depth: " << depth << ", Action: " << a << ", After cfr, Utility: " << actionUtilities[a] << std::endl;
            }
        } else if (a == "CHECK") {
            logFile << "Depth: " << depth << ", Action: " << a << ", Before cfr, Pot Size: " << actionGame.getPotSize() << ", Player Capital: " << actionPlayer.capital << std::endl;
            actionUtilities[a] = cfr(actionGame, actionPlayer, pi1 * piAction, pi2, depth + 1, handSize);
            logFile << "Depth: " << depth << ", Action: " << a << ", After cfr, Utility: " << actionUtilities[a] << std::endl;
        }
    }

    // Calculate the expected utility of the current strategy
    double nodeUtility = 0;
    for (const auto& a : actions) {
        nodeUtility += node.strategy[a] * actionUtilities[a];
    }

    // Log the utilities and node utility
    logFile << "Depth: " << depth << ", Action Utilities: ";
    for (const auto& [action, utility] : actionUtilities) {
        logFile << action << "=" << utility << " ";
    }
    logFile << ", Node Utility: " << nodeUtility << std::endl;

    // Calculate regret and update node regrets
    for (const auto& a : actions) {
        double regret = actionUtilities[a] - nodeUtility;
        node.regrets[a] += (pi2 * regret);
    }

    node.visitCount++;
    return nodeUtility;
}

void MCCFR::train(Game& game, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        Game trainingGame = game;  // Make a copy of the game state for each iteration
        trainingGame.resetPot();
        trainingGame.resetDeck();
        trainingGame.dealHands();
        trainingGame.dealFlop();
        trainingGame.dealTurn();
        trainingGame.dealRiver();
        for (auto& player : trainingGame.getPlayers()) {
            if (player.inGame) {
                logFile << "Iteration: " << i << ", Player: " << player.name << std::endl;
                double utility = cfr(trainingGame, player, 1.0, 1.0, 0, 5);
                logFile << "Iteration: " << i << ", Player: " << player.name << ", Utility: " << utility << std::endl;
            }
        }
    }
}

Action MCCFR::getAction(const Game& game, const Player& player) {
    std::string stateKey = getStateKey(game, player, 5);
    MCCFRNode& node = nodes[stateKey];

    std::string bestAction;
    double bestValue = -1;
    for (const auto& [action, probability] : node.strategySum) {
        double avgProb = probability / node.visitCount;
        if (avgProb > bestValue) {
            bestValue = avgProb;
            bestAction = action;
        }
    }

    if (bestAction == "FOLD") return FOLD;
    if (bestAction == "CALL") return CALL;
    if (bestAction == "RAISE") return RAISE;
    else return CHECK;
}