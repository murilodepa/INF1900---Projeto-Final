#include "../../include/views/Button.h"

Button::Button(float x, float y, float width, float height, Color idleColor, Color hoverColor, Color activeColor)
{
	this->buttonState = BTN_IDLE2;

	this->setPosition(Vector2f(x, y));
	this->setSize(Vector2f(width, height));

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->setFillColor(this->idleColor);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED2) {
		return true;
	}
	return false;
}

void Button::update(const Vector2f(mousePos))
{
	// Idle
	this->buttonState = BTN_IDLE2;

	// Hover
	if (this->getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER2;

		// Pressed
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->buttonState = BTN_PRESSED2;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE2:
		this->setFillColor(this->idleColor);
		break;
	case BTN_HOVER2:
		this->setFillColor(this->hoverColor);
		break;
	case BTN_PRESSED2:
		this->setFillColor(this->activeColor);
	default:
		this->setFillColor(Color::Red);
		break;
	}
}
