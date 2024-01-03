#pragma once
#include <SFML/Graphics.hpp>
#include "../UtilsView.h"

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
            Vector2u initialDeckPosition;
            Sprite** playerHandsCards;

            float cardScale;
            float deckRotation;

            int initialDeckQuantity;

            UtilsView* utilsView;
            
            int numPlayers;
            int cardsInHand;

            float cardWidth; //= playerHands[0][0].getGlobalBounds().width; // 427
            float cardHeight; //= playerHands[0][0].getGlobalBounds().height; // 600
            float halfCard; // = cardWidth / 2;

            void initialize();
            void initializeInitialDeck();
            void initializePlayerHandsCards();


        public:
            CardView(int numPlayers, int cardsInHand);
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
            void setInitialDeck(std::vector<Sprite> initialDeck);
            Vector2u getInitialDeckPosition();
            void setInitialDeckPosition(Vector2u position);

            float getCardScale();
            void setCardScale(float cardScale);
            float getDeckRotation();
            void setDeckRotation(float deckRotation);

            int getInitialDeckQuantity();
            void setInitialDeckQuantity(int initialDeckQuantity);

            void setNumPlayers(int numPlayers);
            void setCardsInHand(int cardsInHand);

            float getCardWidth();
            float getCardHeight();
            float getHalfCard();
        };
    }
}
