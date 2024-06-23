#include "Deck.h"
#include <algorithm>
#include <random>

Deck::Deck() {
    for (int suit = Card::CLUBS; suit <= Card::SPADES; ++suit) {
        for (int rank = Card::TWO; rank <= Card::ACE; ++rank) {
            cards.emplace_back(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit));
        }
    }
    shuffle();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Card Deck::deal() {
    Card dealtCard = cards.back();
    cards.pop_back();
    return dealtCard;
}
