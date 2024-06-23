// GameState.cpp
#include "GameState.h"

GameState::GameState(const std::vector<Card>& hand, const std::vector<Card>& communityCards, int potSize, int myChips, const std::vector<int>& bets)
    : hand(hand), communityCards(communityCards), potSize(potSize), myChips(myChips), bets(bets) {}

std::vector<Card> GameState::getHand() const {
    return hand;
}

std::vector<Card> GameState::getCommunityCards() const {
    return communityCards;
}

int GameState::getPotSize() const {
    return potSize;
}

int GameState::getMyChips() const {
    return myChips;
}

std::vector<int> GameState::getBets() const {
    return bets;
}
