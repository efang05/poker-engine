#include <vector>
#include <card.h>
class Hand {
public:
    Hand(std::vector<Card> hand);

    std::vector<Card>& getHand() const;

    bool operator>(const Hand& h) const;
    
private:
    std::vector<Card>& m_hand;
};