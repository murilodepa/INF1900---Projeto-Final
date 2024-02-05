#ifndef ANIMATOR_H
#define ANIMATOR_H

#pragma once

#include <SFML/Graphics.hpp>
#include "../../../include/views/UtilsView.h"

using namespace sf;

namespace TrucoGame {
    namespace View {
        class Animator {
        public:
            static void moveSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float speed);
            static void moveAndRotateSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float finalRotation, float speed);
            static void rotateSpriteTo(sf::Sprite& sprite, float finalRotation, float speed);
            static void rotateSpriteWithDistanceTo(sf::Sprite& sprite, float finalRotation, float speed, float initialDistance);
            static void moveAndFlipCardTurnedFaceUpTo(sf::Sprite& sprite, Texture* texture, const std::string& newTexturePath, const sf::Vector2f& destinationPosition, float finalRotation, float speed);
            static void animationWithCardTurnedFaceUpAndInitialDeck(sf::Sprite& cardTurnedFaceUp, Texture* texture, const std::string& newTexturePath, sf::Sprite& initialDeck, const sf::Vector2f& cardTurnedFaceUpDestinationPosition, const sf::Vector2f& initialDeckDestinationPosition, float finalRotation, float speed);
            static void flipCard(sf::Sprite& card, float duration, Texture* texture, const std::string& newTexturePath);
        };
    }
}

#endif // ANIMATOR_H
