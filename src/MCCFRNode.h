#ifndef MCCFRNODE_H
#define MCCFRNODE_H

#include <unordered_map>
#include <string>

class MCCFRNode {
public:
    std::unordered_map<std::string, double> regrets;
    std::unordered_map<std::string, double> strategy;
    std::unordered_map<std::string, double> strategySum;
    int visitCount;

    MCCFRNode() : visitCount(0) {}
};

#endif // MCCFRNODE_H
