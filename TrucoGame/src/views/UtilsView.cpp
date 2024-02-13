#include "../../include/views/UtilsView.h"
#include <iostream>

Texture TrucoGame::UtilsView::loadTexture(const std::string texturePath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "ERRO::TrucoGame::Gerenciador::GraphicManager - Failed to find the path of the texture: " << texturePath << std::endl;
        exit(1);
    }
    return texture;
}

Texture TrucoGame::UtilsView::loadTextureBack()
{
    return loadTexture(CARD_BACK_TEXTURE_PATH);
}

Font TrucoGame::UtilsView::loadFont(const std::string fontPath)
{
    sf::Font font;
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("ERROR::TrucoGame::Manager::GraphicManager - Failed to find the font file at path: " + std::string(fontPath));
    }
    return font;
}