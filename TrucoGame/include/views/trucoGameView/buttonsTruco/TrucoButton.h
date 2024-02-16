#ifndef TRUCO_BUTTON_H
#define TRUCO_BUTTON_H

#include "../../../../include/views/button/ButtonBase.h"
#include "../../text/TextView.h"

// Background color of the score rectangle 
#define TRUCO_BUTTON_BACKGROUNG_COLOR Color::Red

// Character size for the player name display
#define CONSTANT_TO_CALCULATE_TRUCO_CHARACTER_SIZE 0.16f

namespace TrucoGame {
    namespace View {
        typedef std::function<void()> TrucoButtonClickEventHandler;

        class TrucoButton : public ButtonBase {

        private:
            bool isButtonAvailable;
            TextView* text;

        protected:
            void onHover();
            void onPressLeft();
            void onPressRight();
            void onIdle();

        public:
            TrucoButton(float x, float y, float width, float height);
            ~TrucoButton();

            bool getIsButtonAvailable();
            void setIsButtonAvailable(bool isButtonAvailable);

            TextView getText();
            TrucoButtonClickEventHandler trucoButtonClick;
        };
    }
}
#endif // TRUCO_BUTTON_H