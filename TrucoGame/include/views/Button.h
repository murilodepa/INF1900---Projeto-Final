#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
using namespace sf;

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

class Button {
private:
    short unsigned buttonState;

    RectangleShape shape;

    Color idleColor;
    Color hoverColor;
    Color activeColor;
public:
    Button(float x, float y, float width, float height, Color idleColor, Color hoverColor, Color activeColor);
    ~Button();

    // Accessors
    const bool isPressed() const;

    // Functions
    void update(const Vector2f(mousePos));
    void render(RenderTarget* target);
};

#endif // BUTTON_H
