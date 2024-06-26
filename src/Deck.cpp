#include "Deck.h"
#include <algorithm>
#include <random>
#include <chrono>

Deck::Deck() {
    const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
    const std::vector<std::string> suits = {"c", "d", "h", "s"};
    for (const auto& rank : ranks) {
        for (const auto& suit : suits) {
            cards.emplace_back(rank, suit);
        }
    }
}

void Deck::shuffle() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

Card Deck::dealCard() {
    Card dealtCard = cards.back();
    cards.pop_back();
    return dealtCard;
}

void Deck::reset() {
    cards.clear();
    const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
    const std::vector<std::string> suits = {"c", "d", "h", "s"};
    for (const auto& rank : ranks) {
        for (const auto& suit : suits) {
            cards.emplace_back(rank, suit);
        }
    }
}
