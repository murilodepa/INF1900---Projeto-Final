#include "../../../include/views/trucoGameView/Animator.h"

namespace TrucoGame {
    namespace View {
        void Animator::moveSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float speed) {
            sf::Vector2f direction = destinationPosition - sprite.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            while (destinationPosition.x != sprite.getPosition().x && destinationPosition.y != sprite.getPosition().y) {
                direction = destinationPosition - sprite.getPosition();
                if (direction.x > speed || direction.y > speed) {
                    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                    // Normalizing the direction to maintain a constant speed
                    sf::Vector2f normalizedDirection = direction / distance;

                    // Moving the sprite in the normalized direction with the specified speed
                    sprite.move(normalizedDirection * speed);

                    // Sleeping to control the animation update rate
                    sf::sleep(sf::milliseconds(16));
                }
                else {
                    sprite.setPosition(destinationPosition);
                }
            }
        }

        void Animator::moveAndRotateSpriteTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float finalRotation, float speed)
        {
            sf::Vector2f direction = destinationPosition - sprite.getPosition();
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            float initialDistance = distance;

            while (destinationPosition.x != sprite.getPosition().x || destinationPosition.y != sprite.getPosition().y || sprite.getRotation() != finalRotation) {
                direction = destinationPosition - sprite.getPosition();
                if (direction.x > speed || direction.y > speed) {
                    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                    // Normalizing the direction to maintain a constant speed
                    sf::Vector2f normalizedDirection = direction / distance;

                    // Moving the sprite in the normalized direction with the specified speed
                    sprite.move(normalizedDirection * speed);

                    rotateSpriteWithDistanceTo(sprite, finalRotation, speed, initialDistance);

                    // Sleeping to control the animation update rate
                    sf::sleep(sf::milliseconds(16));
                }
                else {
                    sprite.setPosition(destinationPosition);
                    sprite.setRotation(finalRotation);
                }
            }
        }

        void Animator::rotateSpriteTo(sf::Sprite& sprite, float finalRotation, float speed)
        {
            // Calculating the gradual rotation
            float rotation = sprite.getRotation();
            float rotationSpeed = std::min(speed, finalRotation - rotation);

            if (rotation < finalRotation - rotationSpeed) {
                sprite.rotate(rotationSpeed);
            }
            else if (rotation != finalRotation) {
                sprite.setRotation(finalRotation);
            }
        }

        void Animator::rotateSpriteWithDistanceTo(sf::Sprite& sprite, float finalRotation, float speed, float initialDistance)
        {
            // Calculating the gradual rotation
            float rotation = sprite.getRotation();
            float rotationSpeed = std::min(speed, finalRotation - rotation) / initialDistance * 100;

            if (rotation < finalRotation - rotationSpeed) {
                sprite.rotate(rotationSpeed);
            }
            else if (rotation != finalRotation) {
                sprite.setRotation(finalRotation);
            }
        }

        void Animator::moveAndFlipCardTurnedFaceUpTo(sf::Sprite& sprite, const sf::Vector2f& destinationPosition, float finalRotation, float speed)
        {
            moveSpriteTo(sprite, destinationPosition, speed);
            flipCard(sprite, 1.5f);
        }

        void Animator::animationWithCardTurnedFaceUpAndInitialDeck(sf::Sprite& cardTurnedFaceUp, sf::Sprite& initialDeck, const sf::Vector2f& cardTurnedFaceUpDestinationPosition, const sf::Vector2f& initialDeckDestinationPosition, float finalRotation, float speed)
        {
            moveAndFlipCardTurnedFaceUpTo(cardTurnedFaceUp, cardTurnedFaceUpDestinationPosition, finalRotation, speed);
            moveAndRotateSpriteTo(initialDeck, initialDeckDestinationPosition, finalRotation, speed);
        }

        void Animator::flipCard(sf::Sprite& card, float duration) {
            // Define a escala inicial da carta
            float initialScaleX = card.getScale().x;

            // Animação de virar a carta
            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < duration) {
                float progress = clock.getElapsedTime().asSeconds() / duration;

                // Ajusta a escala da carta para simular o virar
                card.setScale(initialScaleX * (0.4f - progress), 0.4f);

                // Dorme para controlar a taxa de atualização da animação
                sf::sleep(sf::milliseconds(16));
            }

            // Garante que a escala final seja exatamente 0 para evitar erros numéricos
            //card.setScale(0.0f, 0.4f);
            card.setScale(0.4f, 0.4f);

            card.setPosition(card.getPosition().x - card.getGlobalBounds().width, card.getPosition().y);
        }
    }
}
