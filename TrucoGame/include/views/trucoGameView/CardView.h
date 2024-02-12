#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/UtilsView.h"
#include "CardsEnum.h"

using namespace sf;

namespace TrucoGame {
    namespace View {
        class CardView : public sf::Sprite {
        private:
            //Texture cardTexture;
            float cardScale;
            float cardWidth; //= playerHands[0][0].getGlobalBounds().width; // 427
            float cardHeight; //= playerHands[0][0].getGlobalBounds().height; // 600

        public:
            CardView() = default;
            CardView(Vector2f& cardPositionOnTable, Texture& texture, const float cardScale);
            ~CardView();

            float getCardWidth() const;
            float getCardHeight() const;
            float getHalfCardWidth() const;
        };
    }
}

#endif // CARD_VIEW_H