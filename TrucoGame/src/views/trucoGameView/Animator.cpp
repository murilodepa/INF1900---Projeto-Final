#include "../../../include/views/trucoGameView/Animator.h"

namespace TrucoGame {
	namespace View {
		void Animator::moveSpriteTo(Sprite& sprite, const Vector2f& destinationPosition, float speed) {
			Vector2f direction = destinationPosition - sprite.getPosition();
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			while (destinationPosition.x != sprite.getPosition().x && destinationPosition.y != sprite.getPosition().y) {
				direction = destinationPosition - sprite.getPosition();
				if (direction.x > speed || direction.y > speed) {
					distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

					// Normalizing the direction to maintain a constant speed
					Vector2f normalizedDirection = direction / distance;

					// Moving the sprite in the normalized direction with the specified speed
					sprite.move(normalizedDirection * speed);

					// Sleeping to control the animation update rate
					sleep(milliseconds(16));
				}
				else {
					sprite.setPosition(destinationPosition);
				}
			}
		}

		void Animator::moveAndRotateSpriteTo(Sprite& sprite, const Vector2f& destinationPosition, float finalRotation, float speed)
		{
			Vector2f direction = destinationPosition - sprite.getPosition();
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			float initialDistance = distance;

			while (destinationPosition.x != sprite.getPosition().x || destinationPosition.y != sprite.getPosition().y || sprite.getRotation() != finalRotation) {
				direction = destinationPosition - sprite.getPosition();
				if (direction.x > speed || direction.y > speed) {
					distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

					// Normalizing the direction to maintain a constant speed
					Vector2f normalizedDirection = direction / distance;

					// Moving the sprite in the normalized direction with the specified speed
					sprite.move(normalizedDirection * speed);

					rotateSpriteWithDistanceTo(sprite, finalRotation, speed, initialDistance);

					// Sleeping to control the animation update rate
					sleep(milliseconds(16));
				}
				else {
					sprite.setPosition(destinationPosition);
					sprite.setRotation(finalRotation);
				}
			}
		}

		void Animator::rotateSpriteTo(Sprite& sprite, float finalRotation, float speed)
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

		void Animator::rotateSpriteWithDistanceTo(Sprite& sprite, float finalRotation, float speed, float initialDistance)
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

		void Animator::moveAndFlipCardTurnedFaceUpTo(Sprite& sprite, Texture* texture, const std::string& newTexturePath, const Vector2f& destinationPosition, float finalRotation, float speed)
		{
			moveSpriteTo(sprite, destinationPosition, speed);
			flipCard(sprite, 1.5f, texture, newTexturePath);
		}

		void Animator::animationWithCardTurnedFaceUpAndInitialDeck(Sprite& cardTurnedFaceUp, Texture* texture, const std::string& newTexturePath, Sprite& initialDeck, const Vector2f& cardTurnedFaceUpDestinationPosition, const Vector2f& initialDeckDestinationPosition, float finalRotation, float speed)
		{
			moveAndFlipCardTurnedFaceUpTo(cardTurnedFaceUp, texture, newTexturePath, cardTurnedFaceUpDestinationPosition, finalRotation, speed);
			moveAndRotateSpriteTo(initialDeck, initialDeckDestinationPosition, finalRotation, speed);
		}

		void Animator::flipCard(Sprite& card, float duration, Texture* texture, const std::string& newTexturePath) {

			float initialScaleX = card.getScale().x;

			// Animation to card turned face up
			Clock clock;
			while (clock.getElapsedTime().asSeconds() < duration) {
				float progress = clock.getElapsedTime().asSeconds() / duration;
				float newXValue = initialScaleX * (0.4f - progress);

				// Adjust the card scale to simulate the "vira"
				card.setScale(initialScaleX * (0.4f - progress), 0.4f);

				if (newXValue <= 0.0f) {
					*texture = UtilsView::loadTexture(newTexturePath);
				}


				// Sleep to handle the animation updating
				sleep(milliseconds(16));
			}

			// Make sure that the final scale be exaclty like 0 to avoid numerics mistakes
			card.setScale(0.4f, 0.4f);
			card.setPosition(card.getPosition().x - card.getGlobalBounds().width, card.getPosition().y);
		}
	}
}
