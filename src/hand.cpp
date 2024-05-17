#include <hand.h>

Hand::Hand(std::vector<Card> hand): m_hand(hand) {}

bool Hand::operator>(const Hand& h) const {
    return true;
}

std::vector<Card>& Hand::getHand() const {
    return m_hand;
}