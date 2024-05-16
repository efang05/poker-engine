#include <vector>
#include <card.h>
class Hand {
public:

    void getHand();

    Hand();

    bool operator>(const Hand& h) const;
    
private:
    std::vector<Card> m_hand;
};