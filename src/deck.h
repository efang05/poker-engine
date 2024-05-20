#include <set>
#include <card.h>
class Deck {
public:
    Deck();

    Card getCard();

    void shuffle();
    
private:
    std::set<Card> m_deck;
};