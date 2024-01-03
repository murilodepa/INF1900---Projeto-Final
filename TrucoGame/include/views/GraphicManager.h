#pragma once 

#include <SFML/Graphics.hpp>

#define SCREEN_X 2267.2f
#define SCREEN_Y 1512.0f

namespace TrucoGame {

    namespace View {

        class GraphicManager {
        private:
            sf::RenderWindow* window;

            // The private constructor is part of the Singleton design pattern.
            // It ensures that there is only one instance of the GraphicManager class.
            static GraphicManager* pGraphicManager;
            GraphicManager();
        public:
            ~GraphicManager();
            static GraphicManager* getGraphicManager();
            sf::RenderWindow* getWindow();
            void clearWindow();
            void GraphicManager::drawElement(sf::Sprite sprite);
            void drawElement(sf::RectangleShape rectangleShape);
            void drawElement(sf::Text text);
            void showElements();
            void closeWindow();
            const bool checkWindowOpen();
            const sf::Vector2f getWindowSize() const;
            const sf::Vector2f getHalfWindowSize() const;
            void GraphicManager::checkWindowClose();
        };
    }
}