// TrucoGame.cpp : Defines the entry point for the application.
//

#include <SFML/Graphics.hpp>
#include "../include/Aplicação.h"

int main()
{
    TrucoGame::Aplicação objAplicação;
    objAplicação.executar();
    return 0;
}

// Testar se a SFML (biblioteca gráfica) está funcionando
/*
sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
sf::CircleShape shape(100.f);
shape.setFillColor(sf::Color::Green);

while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
}
*/