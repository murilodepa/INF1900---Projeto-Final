#include "../../../include/views/text/TextView.h"

void TrucoGame::View::TextView::setFontFromPath(const std::string& fontPath)
{
	this->font = UtilsView::loadFont(fontPath);
}

TrucoGame::View::TextView::TextView(const std::string& text, float constantToCalculateCharacterSize, float referenceMeasureToCalculateCharacterSize, Color textColor, Uint32 style)
{
	setFontFromPath(NAME_FONT_PATH);

	this->setFont(font);

	float characterSize = referenceMeasureToCalculateCharacterSize * constantToCalculateCharacterSize;
	this->setCharacterSize(characterSize);
	this->setFillColor(textColor);
	this->setStyle(style);
	this->setString(text);

	sf::FloatRect localBounds = this->getLocalBounds();
	width = localBounds.width;
	height = localBounds.height;
}

TrucoGame::View::TextView::~TextView()
{
}

float TrucoGame::View::TextView::getTextWidth() const
{
	return width;
}

float TrucoGame::View::TextView::getTextHeight() const
{
	return height;
}

float TrucoGame::View::TextView::getHalfTextWidth() const
{
	return width / 2;
}