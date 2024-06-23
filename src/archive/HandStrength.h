#pragma once

#include "HandEvaluator.h"

class HandStrength {
public:
    HandStrength(const Hand& hand);
    
    double getStrength() const;
    HandEvaluator::HandType getHandType() const;
    const std::vector<int>& getRanks() const;

    bool operator>(const HandStrength& other) const;
    bool operator<(const HandStrength& other) const;
    bool operator==(const HandStrength& other) const;
private:
    HandEvaluator::HandType m_type;
    std::vector<int> m_ranks;

    int getHighCard(const Hand& hand) const;
};