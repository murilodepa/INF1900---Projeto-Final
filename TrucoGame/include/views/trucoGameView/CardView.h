#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace TrucoGame {
    namespace View {
        class CardView {
        private:
            Texture cardBackTexture;
            Texture cardFrontTexture;

            Sprite cardTurnedFaceUp;
            Sprite deck;
            std::vector<Sprite> initialDeck;
            Sprite** playerHandsCards;

            float cardScale;
            float deckRotation;

            int initialDeckQuantity;

            int numPlayers;
            int cardsInHand;

            float cardWidth; //= playerHands[0][0].getGlobalBounds().width; // 427
            float cardHeight; //= playerHands[0][0].getGlobalBounds().height; // 600
            float halfCard; // = cardWidth / 2;

            void initialize(Vector2u initialDeckPosition);
            void initializeInitialDeck(Vector2u initialDeckPosition);
            void initializePlayerHandsCards();


        public:
            CardView(int numPlayers, int cardsInHand, Vector2u initialDeckPosition);
            ~CardView();
            Texture getCardBackTexture();
            void setCardBackTexture(const std::string& texturePath);
            Texture getCardFrontTexture();
            void setCardFrontTexture(const std::string& texturePath);

            Sprite getCardTurnedFaceUp();
            void setCardTurnedFaceUp(Sprite cardTurnedFaceUp);
            Sprite getDeck();
            void setDeck(Sprite deck);
            std::vector<Sprite> getInitialDeck();

            float getCardScale();
            void setCardScale(float cardScale);
            float getDeckRotation();
            void setDeckRotation(float deckRotation);

            int getInitialDeckQuantity();
            void setInitialDeckQuantity(int initialDeckQuantity);

            Vector2f getCardPositionInHand(size_t player, size_t card);

            void setNumPlayers(int numPlayers);
            void setCardsInHand(int cardsInHand);
            void setCardPositionsInPlayerHands(Vector2f** cardPositionsOnTable);

            float getCardWidth();
            float getCardHeight();
            float getHalfCardWidth();
        };
    }
}