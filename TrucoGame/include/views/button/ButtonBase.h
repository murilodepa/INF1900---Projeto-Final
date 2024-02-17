#ifndef BUTTON_BASE_H
#define BUTTON_BASE_H

#include <SFML/Graphics.hpp>
#include <functional>

#include "../../../include/views/utils/MutexView.h"
#include "../../../include/views/utils/StatesView.h"

using namespace sf;

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED_LEFT, BTN_PRESSED_RIGHT};

// Hover color of the default rectangle 
#define DEFAULT_BUTTON_HOVER_COLOR Color::Blue

// Character size for the text
#define CONSTANT_TO_CALCULATE_DEFAULT_CHARACTER_SIZE 0.1f

namespace TrucoGame {
    namespace View {
        class ButtonBase : public RectangleShape {
        private:
            short unsigned buttonState;

        protected:
            Color idleColor;
            Color hoverColor;
            Color activeColor;

            virtual void onHover() = 0;
            virtual void onPressLeft() = 0;
            virtual void onPressRight() = 0;
            virtual void onIdle() = 0;

        public:
            ButtonBase(float x, float y, float width, float height);
            ButtonBase(float x, float y, float width, float height, Color idleColor, Color hoverColor, Color activeColor);
            ~ButtonBase();

            // Accessors
            const bool isPressed() const;

            // Functions
            void update(const Vector2f& mousePos);
        };
    }
}

#endif // BUTTON_BASE_H
