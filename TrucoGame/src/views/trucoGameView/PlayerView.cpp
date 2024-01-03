#include "../../../include/views/trucoGameView/PlayerView.h"

void TrucoGame::View::PlayerView::initialize()
{
	setNameFont("../../../../TrucoGame/resources/fonts/Arial.ttf");
}

TrucoGame::View::PlayerView::PlayerView()
{

}

TrucoGame::View::PlayerView::~PlayerView()
{

}

std::vector<Text> TrucoGame::View::PlayerView::getPlayerNames()
{
	return playerNames;
}

void TrucoGame::View::PlayerView::setPlayerNames(std::vector<Text> playerNames)
{
	this->playerNames = playerNames;
}

Font TrucoGame::View::PlayerView::getNameFont()
{
	return nameFont;
}

void TrucoGame::View::PlayerView::setNameFont(const std::string& fontPath)
{
