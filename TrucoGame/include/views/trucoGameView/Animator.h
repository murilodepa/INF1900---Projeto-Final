#ifndef ANIMATOR_H
#define ANIMATOR_H

#pragma once

#include <SFML/Graphics.hpp>
#include "../../../include/views/utils/UtilsView.h"
#include <thread>
#include <ctime>
#include "CardView.h"

// Define to represent the number of players
#define NUM_PLAYERS 4

// Define to represent the number of cards in hand
#define CARDS_IN_HAND 3

using namespace sf;

namespace TrucoGame {
    namespace View {
        class Animator {
        public:
            static void moveSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float speed);
            static void moveAndRotateSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float finalRotation, float speed);
            static void rotateSpriteTo(sf::Sprite& sprite, float finalRotation, float speed);
            static void rotateSpriteWithDistanceTo(sf::Sprite& sprite, float finalRotation, float speed, float initialDistance);
            static void moveAndFlipCardTurnedFaceUpTo(sf::Sprite& sprite, Texture* texture, const std::string& newTexturePath, const sf::Vector2f& destinationPosition, float speed, const float cardScale);
            static void animationWithCardTurnedFaceUpAndInitialDeck(sf::Sprite& cardTurnedFaceUp, Texture* texture, const std::string& newTexturePath, sf::Sprite& initialDeck, const sf::Vector2f& cardTurnedFaceUpDestinationPosition, const sf::Vector2f& initialDeckDestinationPosition, float finalRotation, float speed, const float cardScale);
            static void flipCard(sf::Sprite& card, float duration, Texture* texture, const std::string& newTexturePath, const float cardScale, bool flipHorizontally);
            static void animationToDiscardCard(sf::Sprite& sprite, Texture* texture, const std::string& newTexturePath, Vector2f& destinationPosition, float speed, const float cardScale, float finalRotation, Vector2f& deckPosition);
            static void animationToDiscardMainPlayerCard(sf::Sprite& sprite, Vector2f& destinationPosition, float finalRotation, float speed, Vector2f& deckPosition);
            static void endTurnAndReturnCardsToDeck(Vector2f& deckPosition, float speed);
            static void endRoundAndDistribuiteCards(CardView** cardsInHands, CardView* cardTurnedFaceUp, CardView* deck);
        };
    }
}

#endif // ANIMATOR_H
