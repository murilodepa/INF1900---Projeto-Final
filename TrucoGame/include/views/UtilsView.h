#pragma once 

#include <SFML/Graphics.hpp>

using namespace sf;

namespace TrucoGame {

    namespace View {

        class UtilsView {
        public:
            Texture loadTexture(const std::string texturePath);
            Font loadFont(const std::string fontPath);
        };
    }
}