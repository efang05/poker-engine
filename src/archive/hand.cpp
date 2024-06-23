#include "Hand.h"

void Hand::addCard(const Card& card) {
    cards.push_back(card);
}

const std::vector<Card>& Hand::getCards() const {
    return cards;
}