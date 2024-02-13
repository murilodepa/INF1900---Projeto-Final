#include "../../../../include/views/trucoGameView/Player/PlayerView.h"

void TrucoGame::View::PlayerView::setFontFromPath(const std::string& fontPath)
{
	this->font = UtilsView::loadFont(fontPath);
}

TrucoGame::View::PlayerView::PlayerView(size_t numCardsInHands, const float windowHeight, const std::string& name)
{
	setFontFromPath(NAME_FONT_PATH);
	playerCards.resize(numCardsInHands);

	playerName.setFont(font);

	float playerNameCharacterSize = windowHeight * CONSTANT_TO_CALCULATE_PLAYER_NAME_CHARACTER_SIZE;
	playerName.setCharacterSize(playerNameCharacterSize);
	playerName.setFillColor(NAME_COLOR);
	playerName.setStyle(sf::Text::Bold);

	playerName.setString(name);

	sf::FloatRect localBounds = playerName.getLocalBounds();
	width = localBounds.width;
	height = localBounds.height;
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
	return width;
}

float TrucoGame::View::PlayerView::getTextHeight(size_t playerIndex) const
{
	return height;
}

float TrucoGame::View::PlayerView::getHalfTextWidth(size_t playerIndex) const
{
	return width / 2;
}

Vector2f TrucoGame::View::PlayerView::getCardPosition(size_t cardIndex) const
{
	return playerCards[cardIndex].getPosition();
}