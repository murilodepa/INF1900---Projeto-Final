#include "../../include/views/State.h"

namespace TrucoGame {

    namespace View {

        State::State(RenderWindow* window)
        {
            this->window = window;
            this->quit = false;
        }

        State::~State()
        {

        }

        const bool& State::getQuit() const
        {
            return this->quit;
        }

        void State::checkForQuit()
        {
            // TODO - Quit game
        }

        void State::updateMousePosition()
        {
            this->mousePosScreen = Mouse::getPosition();
            this->mousePosWindow = Mouse::getPosition(*this->window);
            this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
        }
    }
}
