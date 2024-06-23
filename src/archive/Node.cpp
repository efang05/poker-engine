// Node.cpp
#include "Node.h"
#include <numeric>
#include <algorithm>

Node::Node(int numActions) : numActions(numActions), regretSum(numActions, 0.0), strategy(numActions, 0.0), strategySum(numActions, 0.0) {}

std::vector<double> Node::getStrategy() {
    double normalizingSum = 0;
    for (int a = 0; a < numActions; a++) {
        strategy[a] = regretSum[a] > 0 ? regretSum[a] : 0;
        normalizingSum += strategy[a];
    }
    for (int a = 0; a < numActions; a++) {
        strategy[a] = normalizingSum > 0 ? strategy[a] / normalizingSum : 1.0 / numActions;
    }
    return strategy;
}

std::vector<double> Node::getAverageStrategy() {
    std::vector<double> avgStrategy(numActions, 0.0);
    double normalizingSum = std::accumulate(strategySum.begin(), strategySum.end(), 0.0);
    for (int a = 0; a < numActions; ++a) {
        avgStrategy[a] = normalizingSum > 0 ? strategySum[a] / normalizingSum : 1.0 / numActions;
    }
    return avgStrategy;
}

void Node::updateStrategySum(const std::vector<double>& strategy) {
    for (int a = 0; a < numActions; ++a) {
        strategySum[a] += strategy[a];
    }
}

void Node::updateRegretSum(int action, double regret) {
    regretSum[action] += regret;
}