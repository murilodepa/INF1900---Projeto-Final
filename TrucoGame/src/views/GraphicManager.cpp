#include "../../include/views/GraphicManager.h"

namespace TrucoGame {

    namespace Controller {

        GraphicManager* GraphicManager::pGraphicManager = nullptr;

        GraphicManager::GraphicManager() :
            window(new sf::RenderWindow(sf::VideoMode(SCREEN_X, SCREEN_Y), "Truco Game")),
            camera(sf::Vector2f(SCREEN_X, SCREEN_Y))
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
                pGraphicManager = new GraphicManager();
            }
            return pGraphicManager;
        }

        sf::RenderWindow* GraphicManager::getWindow() {
            return window;
        }

        sf::Texture GraphicManager::loadTexture(const char* texturePath) {
            sf::Texture texture;
            if (!texture.loadFromFile(texturePath)) {
                std::cout << "ERRO::TrucoGame::Gerenciador::GraphicManager - Failed to find the path of the texture: " << texturePath << std::endl;
                exit(1);
            }
            return texture;
        }

        sf::Font GraphicManager::loadFont(const char* fontPath) {
            sf::Font font;
            if (!font.loadFromFile(fontPath)) {
                throw std::runtime_error("ERROR::TrucoGame::Manager::GraphicManager - Failed to find the font file at path: " + std::string(fontPath));
            }
            return font;
        }

        void GraphicManager::clearWindow() {
            window->clear();
        }

        void GraphicManager::drawElement(sf::RectangleShape corpo) {
            window->draw(corpo);
        }

        void GraphicManager::drawElement(sf::Text texto) {
            window->draw(texto);
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

        void GraphicManager::updateCamera(const sf::Vector2f pos) {
            camera.update(pos);
            window->setView(camera.getCamera());
        }

        void GraphicManager::updateCamera(const sf::Vector2f pos, sf::Vector2f tam) {
            camera.update(pos, tam);
            window->setView(camera.getCamera());
        }

        const sf::View GraphicManager::getCamera() {
            return camera.getCamera();
        }

        void GraphicManager::resetWindow() {
            camera.reset(sf::Vector2f(SCREEN_X / 2.0f, SCREEN_Y / 2.0f));
            window->setView(camera.getCamera());
        }

        const sf::Vector2f GraphicManager::getWindowSize() const {
            return (sf::Vector2f)window->getSize();
        }

        void GraphicManager::setCameraBoundary(const sf::IntRect cameraBoundary) {
            camera.setCameraBoundary(cameraBoundary);
        }

        void GraphicManager::setObjectBoundary(const sf::IntRect object) {
            camera.setObjectBoundary(object);
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