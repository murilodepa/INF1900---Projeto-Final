#include "../../include/views/MouseState.h"

namespace TrucoGame {

    namespace View {

        MouseState::MouseState(RenderWindow* window)
        {
            this->window = window;
        }

        MouseState::~MouseState()
        {

        }

        void MouseState::updateMousePosition()
        {
            this->mousePosScreen = Mouse::getPosition();
            this->mousePosWindow = Mouse::getPosition(*this->window);
            this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
        }

        Vector2f MouseState::getMousePosView()
        {
            return mousePosView;
        }
    }
}
