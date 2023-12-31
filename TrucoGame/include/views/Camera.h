#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace TrucoGame {

    namespace Controller {

        class Camera {
        private:
            sf::View camera;
            sf::IntRect cameraBoundary;
            sf::IntRect objectBoundary;
            sf::Vector2f windowSize;

            void adjustBoundary();
        public:
            Camera(const sf::Vector2f windowSize);
            ~Camera();
            void setCameraBoundary(const sf::IntRect cameraBoundary);
            void setObjectBoundary(const sf::IntRect objeto);
            sf::View getCamera();
            void reset(const sf::Vector2f posCenter);
            void update(const sf::Vector2f pos);
            void update(const sf::Vector2f pos, sf::Vector2f size);
        };
    }
}