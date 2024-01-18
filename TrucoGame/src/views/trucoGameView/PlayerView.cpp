#include "../../../include/views/trucoGameView/PlayerView.h"

void TrucoGame::View::PlayerView::setFontFromPath(const std::string& fontPath)
{
	this->font = UtilsView::loadFont(fontPath);
}

TrucoGame::View::PlayerView::PlayerView(size_t numCardsInHands)
{
	setFontFromPath(NAME_FONT_PATH);
	playerCards.resize(numCardsInHands);

	playerName.setFont(font);
	playerName.setCharacterSize(PLAYER_NAME_CHARACTER_SIZE);
	playerName.setFillColor(NAME_COLOR);
	playerName.setStyle(sf::Text::Bold);
}

TrucoGame::View::PlayerView::~PlayerView()
{
}

void TrucoGame::View::PlayerView::setPlayerName(std::string name)
{
	this->playerName.setString(name);
}

void TrucoGame::View::PlayerView::setCardPositions(std::vector<Vector2f> cardPositions)
{
	for (size_t i = 0; i < cardPositions.size(); i++) {
		playerCards[i].setPosition(cardPositions[i]);
	}
}

void TrucoGame::View::PlayerView::setNamePosition(Vector2f namePosition)
{
	playerName.setPosition(namePosition);
}

void TrucoGame::View::PlayerView::setNameRotation(float nameRotation)
{
	playerName.setRotation(nameRotation);
}

Text TrucoGame::View::PlayerView::getPlayerName() const
{
	return playerName;
}

float TrucoGame::View::PlayerView::getTextWidth(size_t playerIndex) const
{
	return playerName.getGlobalBounds().width;
}

float TrucoGame::View::PlayerView::getTextHeight(size_t playerIndex) const
{
	return playerName.getGlobalBounds().height;
}

float TrucoGame::View::PlayerView::getHalfTextWidth(size_t playerIndex) const
{
	return playerName.getGlobalBounds().width / 2;
}