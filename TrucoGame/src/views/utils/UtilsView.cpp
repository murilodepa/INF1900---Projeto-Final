#include <iostream>
#include "../../../include/views/utils/UtilsView.h"

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

std::string toString(CardSuit suit) {
    switch (suit) {
    case CardSuit::Hearts:   return "hearts";
    case CardSuit::Diamonds: return "diamonds";
    case CardSuit::Clubs:    return "clubs";
    case CardSuit::Spades:   return "spades";
    default: return "";
    }
}

std::string cardRankToString(CardRank rank) {
    switch (rank) {
    case CardRank::Back:   return "cardBack";
    case CardRank::Ace:    return "ace";
    case CardRank::Jack:   return "jack";
    case CardRank::Queen:  return "queen";
    case CardRank::King:   return "king";
    default:               return std::to_string(static_cast<int>(rank));
    }
}

std::string TrucoGame::UtilsView::findTexturePathByNumberAndSuit(CardStruct& cardStruct)
{
    if (cardStruct.rank == CardRank::Back) {
        return CARD_BACK_TEXTURE_PATH;
    }

    // Construct and return the path to the image file
    return DEFAULT_TEXTURE_PATH + toString(cardStruct.suit) + "/" + cardRankToString(cardStruct.rank) + IMAGE_EXTENSION;
}

Vector2f TrucoGame::UtilsView::getPositionTextInButton(float x, float y, float width, float height, float textWidth, float textHeight)
{
    float textX = x + ((width - textWidth) / 2);
    float textY = y + ((height - textHeight) / 2) - 0.2f * textHeight;
    return Vector2f(textX, textY);
}