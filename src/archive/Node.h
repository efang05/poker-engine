// Node.h
#pragma once
#include <vector>

class Node {
public:
    Node(int numActions);
    std::vector<double> getStrategy();
    std::vector<double> getAverageStrategy();
    void updateStrategySum(const std::vector<double>& strategy);
    void updateRegretSum(int action, double regret);

private:
    std::vector<double> regretSum;
    std::vector<double> strategy;
    std::vector<double> strategySum;
    int numActions;
};