#ifndef CARDS_ENUM_H
#define CARDS_ENUM_H

enum class CardRank {
    Back = 0,
    Ace,
    Two, 
    Three, 
    Four, 
    Five, 
    Six, 
    Seven, 
    Jack, 
    Queen, 
    King,
};

enum class CardSuit {
    Hearts, 
    Diamonds, 
    Clubs, 
    Spades
};

struct Card {
    CardRank rank;
    CardSuit suit;
};

#endif // CARDS_ENUM_H