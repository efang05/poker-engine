// PokerCFR.cpp
#pragma once
#include "PokerCFR.h"
#include "HandEvaluator.h"
#include "Deck.h"

PokerCFR::PokerCFR(int iterations) : iterations(iterations), rng(std::random_device{}()) {}

void PokerCFR::train() {
    for (int t = 0; t < iterations; ++t) {
        std::vector<int> history;
        GameState gameState = generateRandomGameState();
        std::vector<Hand> opponents = generateOpponentHands(2); // Assuming 2 opponents
        cfr(gameState, history, 0, opponents);
    }
}

GameState PokerCFR::generateRandomGameState() {
    Deck deck;
    deck.shuffle();
    
    std::vector<Card> hand = {deck.dealCard(), deck.dealCard()};
    std::vector<Card> communityCards;
    for (int i = 0; i < 5; ++i) {
        communityCards.push_back(deck.dealCard());
    }
    int potSize = std::uniform_int_distribution<int>(50, 200)(rng);
    int myChips = std::uniform_int_distribution<int>(1000, 5000)(rng);
    std::vector<int> bets = {std::uniform_int_distribution<int>(10, 50)(rng), std::uniform_int_distribution<int>(10, 50)(rng)};

    return GameState(hand, communityCards, potSize, myChips, bets);
}

std::vector<Hand> PokerCFR::generateOpponentHands(int numOpponents) {
    Deck deck;
    deck.shuffle();

    std::Here is the continuation of the `PokerCFR` implementation to generate opponent hands and complete the CFR training process:

// ### Generate Opponent Hands and Determine Payoffs

// #### Generate Opponent Hands

// ```cpp
std::vector<Hand> PokerCFR::generateOpponentHands(int numOpponents) {
    Deck deck;
    deck.shuffle();
    std::vector<Hand> opponentHands(numOpponents);
    for (int i = 0; i < numOpponents; ++i) {
        opponentHands[i].addCard(deck.dealCard());
        opponentHands[i].addCard(deck.dealCard());
    }
    return opponentHands;
}