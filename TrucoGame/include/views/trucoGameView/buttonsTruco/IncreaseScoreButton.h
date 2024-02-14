#ifndef INCREASE_SCORE_BUTTON_H
#define INCREASE_SCORE_BUTTON_H

#include "../../../include/views/ButtonBase.h"
#include "../UtilsView.h"

enum class TrucoValue {
    PLUS_6,
    PLUS_9,
    PLUS_12
};

namespace TrucoGame {
    namespace View {
        class IncreaseScoreButton : public ButtonBase {

        private:
            Font textFont;
            Text text;

        protected:
            void onHover();
            void onPressLeft();
            void onPressRight();
            void onIdle();

        public:
            IncreaseScoreButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize);
            ~IncreaseScoreButton();
        };
    }
}
#endif // INCREASE_SCORE_BUTTON_H