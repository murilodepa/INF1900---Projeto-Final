#ifndef CARDS_ENUM_H
#define CARDS_ENUM_H

// Enum representing the ranks of cards
enum class CardRank {
    Back = 0,   // Back of the card
    Ace,        // Ace card
    Two,        // Two card
    Three,      // Three card
    Four,       // Four card
    Five,       // Five card
    Six,        // Six card
    Seven,      // Seven card
    Jack,       // Jack card
    Queen,      // Queen card
    King        // King card
};

// Enum representing the suits of cards
enum class CardSuit {
    Hearts = 3,     // Hearts suit
    Diamonds = 1,   // Diamonds suit
    Clubs = 4,      // Clubs suit
    Spades = 2      // Spades suit
};

// Struct to hold a card's rank and suit
struct CardStruct {
    CardRank rank;  // Rank of the card
    CardSuit suit;  // Suit of the card
};

#endif // CARDS_ENUM_H