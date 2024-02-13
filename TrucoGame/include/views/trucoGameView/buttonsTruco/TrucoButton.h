#ifndef TRUCO_BUTTON_H
#define TRUCO_BUTTON_H

#include "../../../include/views/ButtonBase.h"

namespace TrucoGame {
    namespace View {
        class TrucoButton : public ButtonBase {

        private:
            bool isButtonAvailable;
            Font font;
            float width, height;

            void setFontFromPath(const std::string& fontPath);

        protected:
            void onHover();
            void onPressLeft();
            void onPressRight();
            void onIdle();

        public:
            TrucoButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize);
            ~TrucoButton();

            bool getIsButtonAvailable();
            void setIsButtonAvailable(bool isButtonAvailable);
            float getTextWidth(size_t playerIndex) const;
            float getTextHeight(size_t playerIndex) const;
            float getHalfTextWidth(size_t playerIndex) const;
            Vector2f getCardPosition(size_t cardIndex) const;
        };
    }
}
#endif // TRUCO_BUTTON_H