#include "MCCFR.h"
#include "Evaluator.h"
#include <algorithm>
#include <thread>
#include <iostream>

MCCFR::MCCFR() : rng(std::random_device{}()) {}

std::string MCCFR::getStateKey(const Game& game, const Player& player) {
    std::string key = player.name;
    for (const auto& card : player.hand) {
        key += card.toString();
    }
    for (const auto& card : game.communityCards) {
        key += card.toString();
    }
    return key;
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
    Player& opponent = game.getOpponent(player);

    std::vector<std::string> playerHand;
    for (const auto& card : player.hand) {
        playerHand.push_back(card.toString());
    }
    for (const auto& card : game.communityCards) {
        playerHand.push_back(card.toString());
    }

    std::vector<std::string> opponentHand;
    for (const auto& card : opponent.hand) {
        opponentHand.push_back(card.toString());
    }
    for (const auto& card : game.communityCards) {
        opponentHand.push_back(card.toString());
    }

    HandResult playerResult = evalHand(playerHand);
    HandResult opponentResult = evalHand(opponentHand);

    if (playerResult.value > opponentResult.value) {
        return game.potSize; // Player wins
    } else if (playerResult.value < opponentResult.value) {
        return -game.potSize; // Opponent wins
    } else {
        return 0.0; // Tie
    }
}

double MCCFR::cfr(Game& game, Player& player, double pi1, double pi2, int depth) {
    if (depth > 10 || !player.inGame) return 0;

    std::string stateKey = getStateKey(game, player);
    {
        std::lock_guard<std::mutex> lock(nodesMutex);  // Lock the mutex for thread safety
        MCCFRNode& node = nodes[stateKey];

        if (node.visitCount == 0) {
            // Initialize node if visiting for the first time
            node.regrets = {{"FOLD", 0}, {"CALL", 0}, {"RAISE", 0}};
            node.strategy = {{"FOLD", 1.0 / 3}, {"CALL", 1.0 / 3}, {"RAISE", 1.0 / 3}};
            node.strategySum = {{"FOLD", 0}, {"CALL", 0}, {"RAISE", 0}};
            node.visitCount = 0;
        }
        updateStrategy(node);

        // Log the current state and action probabilities
        {
            std::lock_guard<std::mutex> logLock(logMutex);
            std::cout << "Depth: " << depth << ", State: " << stateKey << ", Strategies: ";
            for (const auto& [action, probability] : node.strategy) {
                std::cout << action << "=" << probability << " ";
            }
            std::cout << std::endl;
        }

        // Select an action based on the current strategy
        std::vector<std::string> actions = {"FOLD", "CALL", "RAISE"};
        std::discrete_distribution<> dist({node.strategy["FOLD"], node.strategy["CALL"], node.strategy["RAISE"]});
        std::string action = actions[dist(rng)];

        double piAction = node.strategy[action];
        std::unordered_map<std::string, double> actionUtilities;
        std::cout << "wtf";
        // Calculate the utility of each action
        for (const auto& a : actions) {
            Player actionPlayer = player;
            Game actionGame = game;

            {
                std::lock_guard<std::mutex> logLock(logMutex);
                std::cout << "Depth: " << depth << ", Action: " << a << std::endl;
            }

            if (a == "FOLD") {
                actionPlayer.inGame = false;
                actionUtilities[a] = 0; // Assume fold has zero utility
            } else if (a == "CALL") {
                if (actionPlayer.capital < 10) {
                    actionPlayer.inGame = false;
                    actionUtilities[a] = -game.potSize;
                } else {
                    actionGame.addToPot(10);
                    actionPlayer.capital -= 10;
                    {
                        std::lock_guard<std::mutex> logLock(logMutex);
                        std::cout << "Depth: " << depth << ", Action: " << a << ", Before cfr, Pot Size: " << actionGame.potSize << ", Player Capital: " << actionPlayer.capital << std::endl;
                    }
                    actionUtilities[a] = cfr(actionGame, actionPlayer, pi1 * piAction, pi2, depth + 1);
                    {
                        std::lock_guard<std::mutex> logLock(logMutex);
                        std::cout << "Depth: " << depth << ", Action: " << a << ", After cfr, Utility: " << actionUtilities[a] << std::endl;
                    }
                }
            } else if (a == "RAISE") {
                if (actionPlayer.capital < 20) {
                    actionPlayer.inGame = false;
                    actionUtilities[a] = -game.potSize;
                } else {
                    actionGame.addToPot(20);
                    actionPlayer.capital -= 20;
                    {
                        std::lock_guard<std::mutex> logLock(logMutex);
                        std::cout << "Depth: " << depth << ", Action: " << a << ", Before cfr, Pot Size: " << actionGame.potSize << ", Player Capital: " << actionPlayer.capital << std::endl;
                    }
                    actionUtilities[a] = cfr(actionGame, actionPlayer, pi1 * piAction, pi2, depth + 1);
                    {
                        std::lock_guard<std::mutex> logLock(logMutex);
                        std::cout << "Depth: " << depth << ", Action: " << a << ", After cfr, Utility: " << actionUtilities[a] << std::endl;
                    }
                }
            }
        }

        // Calculate the expected utility of the current strategy
        double nodeUtility = 0;
        for (const auto& a : actions) {
            nodeUtility += node.strategy[a] * actionUtilities[a];
        }

        // Log the utilities and node utility
        {
            std::lock_guard<std::mutex> logLock(logMutex);
            std::cout << "Depth: " << depth << ", Action Utilities: ";
            for (const auto& [action, utility] : actionUtilities) {
                std::cout << action << "=" << utility << " ";
            }
            std::cout << ", Node Utility: " << nodeUtility << std::endl;
        }

        // Calculate regret and update node regrets
        for (const auto& a : actions) {
            double regret = actionUtilities[a] - nodeUtility;
            node.regrets[a] += (pi2 * regret);
        }

        node.visitCount++;
        return nodeUtility;
    }
}

void MCCFR::train(Game& game, int iterations, int numThreads) {
    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; ++t) {
        threads.emplace_back([this, &game, iterations, numThreads, t]() mutable {
            try {
                for (int i = t; i < iterations; i += numThreads) {
                    Game threadGame = game;  // Make a copy of the game state for each thread
                    threadGame.resetPot();
                    threadGame.dealHands();
                    threadGame.dealFlop();
                    threadGame.dealTurn();
                    threadGame.dealRiver();
                    for (auto& player : threadGame.getPlayers()) {
                        if (player.inGame) {
                            {
                                std::lock_guard<std::mutex> logLock(logMutex);
                                std::cout << "Iteration: " << i << ", Thread: " << t << ", Player: " << player.name << std::endl;
                            }
                            double utility = cfr(threadGame, player, 1.0, 1.0, 0);
                            {
                                std::lock_guard<std::mutex> logLock(logMutex);
                                std::cout << "Iteration: " << i << ", Thread: " << t << ", Player: " << player.name << ", Utility: " << utility << std::endl;
                            }
                        }
                    }
                }
            } catch (const std::exception& e) {
                std::lock_guard<std::mutex> logLock(logMutex);
                std::cerr << "Exception in thread " << t << ": " << e.what() << std::endl;
            } catch (...) {
                std::lock_guard<std::mutex> logLock(logMutex);
                std::cerr << "Unknown exception in thread " << t << std::endl;
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

Action MCCFR::getAction(const Game& game, const Player& player) {
    std::string stateKey = getStateKey(game, player);
    std::lock_guard<std::mutex> lock(nodesMutex);  // Lock the mutex for thread safety
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
    return RAISE;
}
