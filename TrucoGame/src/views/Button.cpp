#include "../../include/views/Button.h"

Button::Button(float x, float y, float width, float height, Color idleColor, Color hoverColor, Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, height));

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED) {
		return true;
	}
	return false;
}

void Button::update(const Vector2f(mousePos))
{
	// Idle
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		// Pressed
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
	default:
		this->shape.setFillColor(Color::Red);
		break;
	}
}

void Button::render(RenderTarget* target)
{
	target->draw(this->shape);
}
