// GameState.h
#pragma once
#include <vector>
#include "Card.h"

class GameState {
public:
    GameState(const std::vector<Card>& hand, const std::vector<Card>& communityCards, int potSize, int myChips, const std::vector<int>& bets);

    std::vector<Card> getHand() const;
    std::vector<Card> getCommunityCards() const;
    int getPotSize() const;
    int getMyChips() const;
    std::vector<int> getBets() const;

private:
    std::vector<Card> hand;
    std::vector<Card> communityCards;
    int potSize;
    int myChips;
    std::vector<int> bets;
};