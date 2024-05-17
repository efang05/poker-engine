class Card {
public:
    enum class Suit {
        Heart,
        Diamond,
        Club,
        Spade
    };

    enum class Rank {
        Two=2,
        Three=3,
        Four=4,
        Five=5,
        Six=6,
        Seven=7,
        Eight=8,
        Nine=9,
        Ten=10,
        Jack=11,
        Queen=12,
        King=13,
        Ace=14
    };

    Card(Suit suit, Rank rank);

    Suit getSuit() const;

    Rank getRank() const;

private:
    Suit m_suit;
    Rank m_rank;    
};