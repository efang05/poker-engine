#include "Player.h"

void Player::addCardToHand(const Card& card) {
    hand.push_back(card);
}

void Player::resetHand() {
    hand.clear();
}
