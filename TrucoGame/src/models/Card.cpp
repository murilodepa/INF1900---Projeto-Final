#include "../../include/models/Card.h"

namespace TrucoGame {

    namespace Models {
        Card::Card(int value, Suit suit) : value(value), suit(suit)
        {

        }

        Card::Card(const nlohmann::json& j):
            Card(j.at("value").get<int>(), static_cast<Suit>(j.at("suit").get<int>()))
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
        int Card::getNumber() {
            switch (value) {
            case 0:
                return 4;
            case 1:
                return 5;
            case 2:
                return 6;
            case 3:
                return 7;
            case 4:
                return 9;
            case 5:
                return 8;
            case 6:
                return 10;
            case 7:
                return 1;
            case 8:
                return 2;
            case 9:
                return 3;
            }
        }

        void Card::ToJson(nlohmann::json& j) const {
            j["value"] = value;
            j["suit"] = suit;
        }

        //USE: Card myCard = Card::FromJson(jsonData);
        Card Card::FromJson(const nlohmann::json& j) {
            int value = j.at("value").get<int>();
            Suit suit = static_cast<Suit>(j.at("suit").get<int>());
           
            return Card(value, suit);
        }
    }
}