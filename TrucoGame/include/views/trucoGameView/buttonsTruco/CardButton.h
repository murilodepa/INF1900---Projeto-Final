#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "../../../../include/views/button/ButtonBase.h"
#include "../../utils/UtilsView.h"

#include <functional>

namespace TrucoGame {
    namespace View {

        typedef std::function<void(int, bool)> CardButtonClickEventHandler;

        class CardButton : public ButtonBase {

        private:
            Sprite* card;
            bool areCardsInTheHandsOfThePlayer;
            Vector2f discardOnTheTablePosition;
            float animationSpeed;
            Texture* cardTexture;
            size_t cardIndex;

            void discardCardOnTheTable();

        protected:
            void onHover();
            void onPressLeft();
            void onPressRight();
            void onIdle();

        public:
            CardButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize, float animationSpeed, Vector2f& discardOnTheTablePosition, Texture* cardTexture, size_t cardIndex);
            ~CardButton();

            bool getAreCardsInTheHandsOfThePlayer();
            void setAreCardsInTheHandsOfThePlayer(bool areCardsInTheHandsOfThePlayer);
            CardButtonClickEventHandler cardButtonClick;
        };
    }
}
#endif // CARD_BUTTON_H