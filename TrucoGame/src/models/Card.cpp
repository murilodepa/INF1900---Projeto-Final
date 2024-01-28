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