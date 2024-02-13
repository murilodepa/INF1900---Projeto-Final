#ifndef BUTTON_BASE_H
#define BUTTON_BASE_H

#include <SFML/Graphics.hpp>
using namespace sf;

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED_LEFT, BTN_PRESSED_RIGHT};

class ButtonBase : public RectangleShape {
private:
    short unsigned buttonState;

protected:
    Color idleColor;
    Color hoverColor;
    Color activeColor;

    virtual void onHover() = 0;
    virtual void onPressLeft() = 0;
    virtual void onPressRight() = 0;
    virtual void onIdle() = 0;

public:
    ButtonBase(float x, float y, float width, float height, Color hoverColor);
    ButtonBase(float x, float y, float width, float height, Color idleColor, Color hoverColor, Color activeColor);
    ~ButtonBase();

    // Accessors
    const bool isPressed() const;

    // Functions
    void update(const Vector2f& mousePos);
};

#endif // BUTTON_BASE_H
