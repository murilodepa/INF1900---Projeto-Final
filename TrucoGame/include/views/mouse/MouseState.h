#ifndef MOUSE_STATE_H
#define MOUSE_STATE_H

#include <SFML/Graphics.hpp>
using namespace sf;

namespace TrucoGame {

    namespace View {
        class MouseState {

        protected:
            RenderWindow* window;
            Vector2i mousePosScreen;
            Vector2i mousePosWindow;
            Vector2f mousePosView;

        public:
            MouseState(RenderWindow* window);
            ~MouseState();

            void updateMousePosition();
            Vector2f getMousePosView();
        };

        #endif // MOUSE_STATE_H
    }
}