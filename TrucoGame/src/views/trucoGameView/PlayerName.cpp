#include "../../../include/views/trucoGameView/PlayerName.h"
#include "../../../include/views/UtilsView.h"

TrucoGame::View::PlayerName::PlayerName(size_t numPlayers)
{
	setFontFromPath(NAME_FONT_PATH);
	playerNamesText.resize(numPlayers);

	for (size_t i = 0; i < numPlayers; i++) {
		playerNamesText[i].setFont(font);
		playerNamesText[i].setCharacterSize(PLAYER_NAME_CHARACTER_SIZE);
		playerNamesText[i].setFillColor(sf::Color::White);
		playerNamesText[i].setStyle(sf::Text::Bold);
	}

}

TrucoGame::View::PlayerName::~PlayerName()
{

}

void TrucoGame::View::PlayerName::setFontFromPath(const std::string& fontPath)
{
	this->font = UtilsView::loadFont(fontPath);
}

Text TrucoGame::View::PlayerName::getPlayerName(size_t playerIndex)
{
	return playerNamesText[playerIndex];
}

void TrucoGame::View::PlayerName::setPlayerNames(std::vector<std::string> names)
{
	for (size_t i = 0; i < names.size(); i++) {
		playerNamesText[i].setString(names[i]);
	}
}

float TrucoGame::View::PlayerName::getTextWidth(size_t playerIndex) const
{
	return playerNamesText[playerIndex].getGlobalBounds().width;
}

float TrucoGame::View::PlayerName::getTextHeight(size_t playerIndex) const
{
	return playerNamesText[playerIndex].getGlobalBounds().height;
}

float TrucoGame::View::PlayerName::getHalfTextWidth(size_t playerIndex) const
{
	return playerNamesText[playerIndex].getGlobalBounds().width / 2;
}

void TrucoGame::View::PlayerName::setPositionOfPlayerName(size_t playerIndex, Vector2f namePosition)
{
	playerNamesText[playerIndex].setPosition(namePosition);
}

void TrucoGame::View::PlayerName::setRotationOfPlayerName(size_t playerIndex, float nameRotation)
{
	playerNamesText[playerIndex].setRotation(nameRotation);
}
