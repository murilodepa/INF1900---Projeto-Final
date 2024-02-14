#include "../../../../include/views/trucoGameView/buttonsTruco/TrucoButton.h"

void TrucoGame::View::TrucoButton::onPressLeft()
{
}

void TrucoGame::View::TrucoButton::onPressRight()
{
	// TODO - Pedir Truco
}

void TrucoGame::View::TrucoButton::onHover() {
	this->setOutlineColor(DEFAULT_BUTTON_HOVER_COLOR);
	this->setOutlineThickness(4);
}

void TrucoGame::View::TrucoButton::onIdle() {
	this->setOutlineColor(Color::White);
	this->setOutlineThickness(2);
}

TrucoGame::View::TrucoButton::TrucoButton(float x, float y, float width, float height) :
	ButtonBase(x, y, width, height)
{
	this->setFillColor(TRUCO_BUTTON_BACKGROUNG_COLOR);
	this->setOutlineColor(DEFAULT_BUTTON_HOVER_COLOR);

	text = new TextView("TRUCAR", CONSTANT_TO_CALCULATE_TRUCO_CHARACTER_SIZE, width, Color::White, Text::Bold);
	text->setPosition(UtilsView::getPositionTextInButton(x, y, width, height, text->getTextWidth(), text->getTextHeight()));
}

TrucoGame::View::TrucoButton::~TrucoButton()
{
}

bool TrucoGame::View::TrucoButton::getIsButtonAvailable() {
	return isButtonAvailable;
}

void TrucoGame::View::TrucoButton::setIsButtonAvailable(bool isButtonAvailable) {
	this->isButtonAvailable = isButtonAvailable;
}

TrucoGame::View::TextView TrucoGame::View::TrucoButton::getText()
{
	return *text;
}