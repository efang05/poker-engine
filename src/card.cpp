#include <card.h>

Card::Card(Card::Suit suit, Card::Rank rank): m_suit(suit), m_rank(rank) {}

Card::Suit Card::getSuit() const { return m_suit; }

Card::Rank Card::getRank() const { return m_rank; }