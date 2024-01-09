#pragma once 

#include <SFML/Graphics.hpp>

using namespace sf;

namespace TrucoGame {

    namespace UtilsView {

        Texture loadTexture(const std::string texturePath);
        Font loadFont(const std::string fontPath);
        
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

        template <typename Function, typename... Args>
        void createThread(Function&& function, Args&&... args) {
            std::thread(std::forward<Function>(function), std::forward<Args>(args)...).detach();
        }
    }
}