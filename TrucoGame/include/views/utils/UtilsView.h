#pragma once 

#include <SFML/Graphics.hpp>
#include "CardsEnum.h"

// Define the default path for the card textures
#define DEFAULT_TEXTURE_PATH "../../../../TrucoGame/resources/images/cards/"

// Define the full path for the texture of the card back
#define CARD_BACK_TEXTURE_PATH "../../../../TrucoGame/resources/images/cards/cardBack.png"

// Define the default extension for image files
#define IMAGE_EXTENSION ".png"

using namespace sf;

namespace TrucoGame {

    namespace UtilsView {

        Texture loadTexture(const std::string texturePath);
        Texture loadTextureBack();
        Font loadFont(const std::string fontPath);
        std::string findTexturePathByNumberAndSuit(CardStruct& cardStruct);
        Vector2f getPositionTextInButton(float x, float y, float width, float height, float textWidth, float textHeight);

        template <typename T>
        inline T** initializeMatrix(int rows, int columns) {
            T** matrix = new T * [rows];
            for (int i = 0; i < rows; i++) {
                matrix[i] = new T[columns];
                for (int j = 0; j < columns; j++) {
                    matrix[i][j] = T();
                }
            }
            return matrix;
        }
        
        template <typename U>
        inline void freeMatrix(U** matrix, int rows) {
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }
}