#include <card.h>

Card::Card(Card::Suit suit, Card::FaceValue value) {
    m_suit = suit;
    m_facevalue = value;
}

Card::Suit Card::getSuit() {
    return m_suit;
}

Card::FaceValue Card::getFaceValue() {
    return m_facevalue;
}