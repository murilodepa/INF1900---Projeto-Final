#include "../../include/models/Card.h"

namespace TrucoGame {

    namespace Models {
        Card::Card(int value, Suit suit) : value(value), suit(suit)
        {

        }

        Card::~Card() {
        }

        int Card::getValue() {
            return value;
        }

        Suit Card::getSuit() {
            return suit;
        }
    }
}