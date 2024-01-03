#include "../../include/models/Card.h"

namespace TrucoGame {

    namespace Models {

        Card::Card(int value, string suit)
        {
            this->value = value;
            this->suit = suit;
        }

        Card::~Card() {
        }

        int Card::getValor() {
            return value;
        }

        string Card::getSuit() {
            return suit;
        }
    }
}