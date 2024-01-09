#include "../../include/models/Card.h"

namespace TrucoGame {

    namespace Models {
        Card::Card(int value, Suit suit) : value(value), suit(suit)
        {
            //Load file -> texture -> sprite
            texture.loadFromFile(getSpritePath());

            //Config sprite
            sprite.setScale(0.4f, 0.4f);
        }

        Card::~Card() {
        }

        int Card::getValue() {
            return value;
        }

        Suit Card::getSuit() {
            return suit;
        }

        sf::Sprite* Card::getSprite() {
            sprite.setTexture(texture);

            return &sprite;
        }

        std::string Card::getSpritePath() {
            std::string pathToSprite = "../../../../TrucoGame/resources/images/cards/";
            std::string suitName;

            switch (suit) {
                case Suit::Clubs:
                    suitName = "clubs";
                    break;
                case Suit::Spades:
                    suitName = "spades";
                    break;
                case Suit::Diamonds:
                    suitName = "diamonds";
                    break;
                case Suit::Hearts:
                    suitName = "hearts";
                    break;
            }

            pathToSprite.append(suitName);
            pathToSprite.append("/");
            pathToSprite.append(std::to_string(value));
            pathToSprite.append(".png");

            return pathToSprite;
        }
    }
}