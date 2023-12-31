#pragma once 

#define SCREEN_X 2000.0f
#define SCREEN_Y 1600.0f

#include "Camera.h"

namespace TrucoGame {

    namespace Controller {

        class GraphicManager {
        private:
            sf::RenderWindow* window;

            // Move the camera
            Camera camera;

            // The private constructor is part of the Singleton design pattern.
            // It ensures that there is only one instance of the GraphicManager class.
            static GraphicManager* pGraphicManager;
            GraphicManager();
        public:
            ~GraphicManager();
            static GraphicManager* getGraphicManager();
            sf::RenderWindow* getWindow();
            sf::Texture loadTexture(const char* texturePath);
            sf::Font loadFont(const char* fontPath);
            void clearWindow();
            void drawElement(sf::RectangleShape shape);
            void drawElement(sf::Text text);
            void showElements();
            void closeWindow();
            const bool checkWindowOpen();
            void updateCamera(const sf::Vector2f pos);
            void updateCamera(const sf::Vector2f pos, sf::Vector2f size);
            const sf::View getCamera();
            void resetWindow();
            const sf::Vector2f getWindowSize() const;
            void setCameraBoundary(const sf::IntRect cameraBoundary);
            void setObjectBoundary(const sf::IntRect object);
            void GraphicManager::checkWindowClose();
        };
    }
}