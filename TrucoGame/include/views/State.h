#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
using namespace sf;

namespace TrucoGame {

    namespace View {
        class State {

        protected:
            RenderWindow* window;
            Vector2i mousePosScreen;
            Vector2i mousePosWindow;
            Vector2f mousePosView;

            bool quit;

        public:
            State(RenderWindow* window);
            ~State();

            const bool& getQuit() const;
            virtual void checkForQuit();
            virtual void endState() = 0;
            virtual void updateMousePosition();
            virtual void render(RenderTarget* target = NULL) = 0;
        };

        #endif // STATE_H
    }
}