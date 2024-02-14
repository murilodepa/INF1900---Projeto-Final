#include "../../../include/views/button/ButtonBase.h"

TrucoGame::View::ButtonBase::ButtonBase(float x, float y, float width, float height)
{
	this->buttonState = BTN_IDLE;

	this->setPosition(Vector2f(x, y));
	this->setSize(Vector2f(width, height));
}

TrucoGame::View::ButtonBase::ButtonBase(float x, float y, float width, float height, Color idleColor, Color hoverColor, Color activeColor) :
	ButtonBase(x, y, width, height)
{
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

TrucoGame::View::ButtonBase::~ButtonBase()
{
}

const bool TrucoGame::View::ButtonBase::isPressed() const
{
	if (this->buttonState == BTN_PRESSED_LEFT) {
		return true;
	}
	return false;
}

void TrucoGame::View::ButtonBase::update(const Vector2f& mousePos)
{
	// Idle
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		// Pressed
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->buttonState = BTN_PRESSED_LEFT;
		}
		else if (Mouse::isButtonPressed(Mouse::Right)) {
			this->buttonState = BTN_PRESSED_RIGHT;
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
	case BTN_PRESSED_LEFT:
		onPressLeft();
		break;
	case BTN_PRESSED_RIGHT:
		onPressRight();
		break;
	default:
		break;
	}
}