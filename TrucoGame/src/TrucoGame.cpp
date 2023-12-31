// TrucoGame.cpp : Defines the entry point for the application.

#include <SFML/Graphics.hpp>
#include "../include/controllers/Application.h"

int main()
{
    TrucoGame::Application applicationObject;
    applicationObject.run();
    return 0;
}