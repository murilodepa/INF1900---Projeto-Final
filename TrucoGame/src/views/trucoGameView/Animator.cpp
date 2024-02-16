#include "../../../include/views/trucoGameView/Animator.h"
#include "../../../include/views/utils/MutexView.h"
#include "../../../include/views/utils/StatesView.h"

namespace TrucoGame {
	namespace View {
		void Animator::moveSpriteTo(Sprite& sprite, const Vector2f& destinationPosition, float speed) {
			Vector2f direction = destinationPosition - sprite.getPosition();
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			clock_t startTime = clock();

			while (destinationPosition.x != sprite.getPosition().x && destinationPosition.y != sprite.getPosition().y 
				&& (clock() - startTime) / CLOCKS_PER_SEC <= 5) {
				direction = destinationPosition - sprite.getPosition();
				if (std::abs(direction.x) > speed || std::abs(direction.y) > speed) {
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

			clock_t startTime = clock();

			while (destinationPosition.x != sprite.getPosition().x || destinationPosition.y != sprite.getPosition().y || sprite.getRotation() != finalRotation
				&& (clock() - startTime) / CLOCKS_PER_SEC <= 5) {
				direction = destinationPosition - sprite.getPosition();
				if (std::abs(direction.x) > speed || std::abs(direction.y) > speed) {
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
			if (rotation == finalRotation && finalRotation != 0) {
				finalRotation = finalRotation + rotation;
			}
			float rotationSpeed = std::min(speed, finalRotation - rotation) / initialDistance * 100;

			if (rotation < finalRotation - rotationSpeed) {
				sprite.rotate(rotationSpeed);
			}
			else if (rotation != finalRotation) {
				sprite.setRotation(finalRotation);
			}
		}

		void Animator::moveAndFlipCardTurnedFaceUpTo(Sprite& sprite, Texture* texture, const std::string& newTexturePath, const Vector2f& destinationPosition, float speed, const float cardScale)
		{
			moveSpriteTo(sprite, destinationPosition, speed);
			flipCard(sprite, 0.5f, texture, newTexturePath, cardScale, true);
		}

		void Animator::animationWithCardTurnedFaceUpAndInitialDeck(Sprite& cardTurnedFaceUp, Texture* texture, const std::string& newTexturePath, Sprite& initialDeck, const Vector2f& cardTurnedFaceUpDestinationPosition, const Vector2f& initialDeckDestinationPosition, float finalRotation, float speed, const float cardScale)
		{
			moveAndFlipCardTurnedFaceUpTo(cardTurnedFaceUp, texture, newTexturePath, cardTurnedFaceUpDestinationPosition, speed, cardScale);
			moveAndRotateSpriteTo(initialDeck, initialDeckDestinationPosition, finalRotation, speed);
		}

		void Animator::flipCard(Sprite& card, float duration, Texture* texture, const std::string& newTexturePath, const float cardScale, bool flipHorizontally) {

			float initialScaleX = card.getScale().x;

			// Animation to card turned face up
			Clock clock;
			while (clock.getElapsedTime().asSeconds() < duration) {
				float progress = clock.getElapsedTime().asSeconds() / duration;
				float newXValue = initialScaleX * (cardScale - progress);

				// Adjust the card scale to simulate the "vira"
				card.setScale(initialScaleX * (cardScale - progress), cardScale);

				if (newXValue <= 0.0f) {
					*texture = UtilsView::loadTexture(newTexturePath);
				}


				// Sleep to handle the animation updating
				sleep(milliseconds(16));
			}

			// Make sure that the final scale be exaclty like 0 to avoid numerics mistakes
			card.setScale(cardScale, cardScale);
			if (flipHorizontally) {
				card.setPosition(card.getPosition().x - card.getGlobalBounds().width, card.getPosition().y);
			}
			else {
				card.setPosition(card.getPosition().x, card.getPosition().y - card.getGlobalBounds().width);
			}
		}

		void Animator::animationToDiscardCard(sf::Sprite& sprite, Texture* texture, const std::string& newTexturePath, sf::Vector2f& destinationPosition, float speed, const float cardScale, float finalRotation, Vector2f& deckPosition, CardView** cardsInHands, CardView* cardTurnedFaceUp, CardView* deck) {
			cardMutex.lock();
			if (cardState == CardState::Covered) 
			{
				destinationPosition.y = destinationPosition.y - sprite.getGlobalBounds().width;
			}
			cardMutex.unlock();
			
			if (finalRotation != 0) {
				moveAndRotateSpriteTo(sprite, destinationPosition, finalRotation, speed);
			}
			else 
			{
				moveSpriteTo(sprite, destinationPosition, speed);
			}

			cardMutex.lock();
			if (cardState != CardState::Covered)
			{
				flipCard(sprite, 0.5f, texture, newTexturePath, cardScale, false);
			}
			cardMutex.unlock();
			endTurnAndReturnCardsToDeck(deckPosition, cardsInHands, speed, cardTurnedFaceUp, deck);
		}

		void Animator::animationToDiscardMainPlayerCard(sf::Sprite& sprite, Vector2f& destinationPosition, float finalRotation, float speed, Vector2f& deckPosition, CardView** cardsInHands, CardView* cardTurnedFaceUp, CardView* deck)
		{
			moveAndRotateSpriteTo(sprite, destinationPosition, finalRotation, speed);
			endTurnAndReturnCardsToDeck(deckPosition, cardsInHands, speed, cardTurnedFaceUp, deck);
		}

		void Animator::endTurnAndReturnCardsToDeck(Vector2f& deckPosition, CardView** cardsInHands, float speed, CardView* cardTurnedFaceUp, CardView* deck)
		{
			roundAndTurnMutex.lock();
			RoundAndTurnState roundAndTurnStateLocal = roundAndTurnState;
			roundAndTurnState = RoundAndTurnState::RoundAndTurnRunning;
			roundAndTurnMutex.unlock();

			if (roundAndTurnStateLocal == RoundAndTurnState::TurnEnded) {
				std::chrono::seconds sleepDuration(1);
				std::this_thread::sleep_for(sleepDuration);
				changePlayersCardsOnTheTableMutex.lock();
				for (Sprite* card : playersCardsOnTheTable) {
					moveAndRotateSpriteTo(*card, deckPosition, 35, speed);
				}
				playersCardsOnTheTable.clear();
				changePlayersCardsOnTheTableMutex.unlock();
			}
			else if (roundAndTurnStateLocal == RoundAndTurnState::RoundEnded) {
				std::chrono::seconds sleepDuration(1);
				std::this_thread::sleep_for(sleepDuration);
				for (size_t player = 0; player < 4; player++) {
					for (size_t card = 0; card < 3; card++) {
						Sprite* cardSprite = &cardsInHands[player][card];
						cardSprite->setRotation(0);
						cardSprite->setPosition(Vector2f(0, 0));
					}
				}
				cardTurnedFaceUp->setRotation(0);
				cardTurnedFaceUp->setPosition(Vector2f(0, 0));
				deck->setRotation(0);
				deck->setPosition(Vector2f(0, 0));

				distributeCardsToPlayersMutex.lock();
				distributeCardsToPlayersState = DistributeCardsToPlayersState::Distribute;
				distributeCardsToPlayersMutex.unlock();
			}
		}
	}
}
