#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
using namespace sf;

enum button_states2{BTN_IDLE2 = 0, BTN_HOVER2, BTN_PRESSED2};

class Button : public RectangleShape {
private:
    short unsigned buttonState;

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
};

#endif // BUTTON_H
