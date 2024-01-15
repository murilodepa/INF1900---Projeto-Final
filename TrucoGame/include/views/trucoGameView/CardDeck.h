#ifndef CARD_DECK_H
#define CARD_DECK_H


#pragma once
#include <SFML/Graphics.hpp>
#include "CardView.h"

#define CARD_BACK_TEXTURE_PATH "../../../../TrucoGame/resources/images/cards/cardBack.png"
#define DEFAULT_TEXTURE_PATH "../../../../TrucoGame/resources/images/cards/"

using namespace sf;

namespace TrucoGame {
    namespace View {
        class CardDeck : public CardView {
        private:
            Texture cardTexture;
            size_t quantityOfCards;

            CardView* cardTurnedFaceUp;
            CardView* deck;

        public:
            CardView** cardsInHands;

            CardDeck() = default;
            CardDeck(size_t numPlayer, size_t quantityOfCardsInHands, Vector2f& initialDeckPositionVector2f);
            ~CardDeck();

            Texture getCardTexture();
            void setCardTexture(Card &card);

            CardView* getCardTurnedFaceUp();
            CardView* getDeck();

            size_t getQuantityOfCards();

            void initializeCardDeck(size_t numPlayer, size_t quantityOfCardsInHands, Vector2f& initialDeckPositionVector2f);
        };
    }
}

#endif // CARD_DECK_H