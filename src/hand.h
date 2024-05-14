#include <vector>
#include <card.h>
class Hand {
public:

    void getHand();

    Hand();
    
private:
    std::vector<Card> m_hand;
};