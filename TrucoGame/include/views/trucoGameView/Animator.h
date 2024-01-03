#pragma once

#include <SFML/Graphics.hpp>

namespace TrucoGame {
    namespace View {
        class Animator {
        public:
            static void moveSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float speed);
            static void moveAndRotateSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float finalRotation, float speed);
            static void flipCard(sf::Sprite& card, float duration);
        };
    }
}
