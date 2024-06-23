#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
public:
    Deck();

    void shuffle();
    Card deal();

private:
    std::vector<Card> cards;
};

#endif // DECK_H