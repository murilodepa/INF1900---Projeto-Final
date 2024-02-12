#include "../../include/views/GraphicManager.h"
#include <iostream>

namespace TrucoGame {

    namespace View {

        GraphicManager* GraphicManager::pGraphicManager = nullptr;

        GraphicManager::GraphicManager(unsigned int windowWidth, unsigned int windowHeight) :
            window(new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Truco Game", sf::Style::Titlebar | sf::Style::Close))
        {
            if (window == nullptr) {
                std::cout << "ERROR::TrucoGame::Controller::GraphicManager - Failed to create a graphical window." << std::endl;
                exit(1);
            }
            window->setFramerateLimit(0);
        }

        GraphicManager::~GraphicManager() {
            if (window) {
                delete(window);
                window = nullptr;
            }
        }

        GraphicManager* GraphicManager::getGraphicManager() {
            /**
             * @ return GraphicManager*
             *
             * Singleton Design Pattern: ensures that there is only one instance in my project as a whole, that is,
             * it is not possible to create two different objects of this type.
             */

            if (pGraphicManager == nullptr) {
                sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
                unsigned int windowHeight = desktop.height - 100;
                unsigned int windowWidth = static_cast<int>(windowHeight * 1.499470899470899f);
                if (windowWidth > desktop.width)
                    windowWidth = desktop.width;
                pGraphicManager = new GraphicManager(windowWidth, windowHeight);
            }
            return pGraphicManager;
        }

        sf::RenderWindow* GraphicManager::getWindow() {
            return window;
        }

        void GraphicManager::clearWindow() {
            window->clear();
        }

        void GraphicManager::drawElement(sf::Sprite& sprite) {
            window->draw(sprite);
        }

        void GraphicManager::drawElement(CardView& cardView) {
            window->draw(cardView);
        }
        
        void GraphicManager::drawElement(Button& button) {
            window->draw(button);
        }

        void GraphicManager::drawElement(sf::RectangleShape& rectangleShape) {
            window->draw(rectangleShape);
        }

        void GraphicManager::drawElement(sf::CircleShape& circleShape) {
            window->draw(circleShape);
        }

        void GraphicManager::drawElement(sf::Text& text) {
            window->draw(text);
        }

        void GraphicManager::showElements() {
            window->display();
        }

        void GraphicManager::closeWindow() {
            if (window->isOpen()) {
                window->close();
            }
        }

        const bool GraphicManager::checkWindowOpen() {
            return window->isOpen();
        }

        const sf::Vector2f GraphicManager::getWindowSize() const {
            return (sf::Vector2f)window->getSize();
        }

        const sf::Vector2f GraphicManager::getHalfWindowSize() const {
            sf::Vector2u windowSize = window->getSize();
            return sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f);
        }

        void GraphicManager::checkWindowClose() {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    closeWindow();
            }
        }
    }
}