#include "../../include/views/ButtonBase.h"

ButtonBase::ButtonBase(float x, float y, float width, float height, Color hoverColor)
{
	this->buttonState = BTN_IDLE;

	this->setPosition(Vector2f(x, y));
	this->setSize(Vector2f(width, height));

	this->hoverColor = hoverColor;
}

ButtonBase::ButtonBase(float x, float y, float width, float height, Color idleColor, Color hoverColor, Color activeColor) :
	ButtonBase(x, y, width, height, hoverColor)
{
	this->idleColor = idleColor;
	this->activeColor = activeColor;
}

ButtonBase::~ButtonBase()
{
}

const bool ButtonBase::isPressed() const
{
	if (this->buttonState == BTN_PRESSED) {
		return true;
	}
	return false;
}

void ButtonBase::update(const Vector2f& mousePos)
{
	// Idle
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		// Pressed
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		onIdle();
		break;
	case BTN_HOVER:
		onHover();
		break;
	case BTN_PRESSED:
		onPress();
		break;
	default:
		break;
	}
}
