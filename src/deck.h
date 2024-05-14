#include <set>
#include <card.h>
class Deck {
public:
    Deck();

    Card getCard();

    void shuffle();
    
private:
    // think about using map of suits to values or set of cards
    std::set<Card> m_deck;
};