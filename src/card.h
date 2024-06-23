#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
    enum Rank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

    Card(Rank r, Suit s);

    std::string toString() const;
    Rank getRank() const;
    Suit getSuit() const;

private:
    Rank rank;
    Suit suit;
};

#endif // CARD_H
