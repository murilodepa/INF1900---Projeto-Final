#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "Button.h"

namespace TrucoGame {

    namespace View {
        class MainMenuState : public State {
        private:
            Button* button;

        public:
            MainMenuState(RenderWindow* window);
            virtual ~MainMenuState();

            void endState();

            void update(/*const float& dt*/);
            void render(RenderTarget* target = NULL);
        };

        #endif // MAIN_MENU_STATE_H
    } // namespace View
} // namespace TrucoGame