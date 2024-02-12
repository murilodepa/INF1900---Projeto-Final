#include "../../../include/views/trucoGameView/TrucoGameView.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"

void TrucoGame::View::TrucoGameView::initialize(const Vector2f& windowSize)
{
	for (size_t playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++) {
		PlayerView* player = new PlayerView(CARDS_IN_HAND, windowSize.y);
		players.push_back(player);
	}

	if (playerCards.cardsInHands != nullptr) {
		float tableAndCardsSpacing = windowSize.y * CALCULATE_TABLE_AND_CARDS_SPACING;
		float cardsSpacing = windowSize.x * CALCULATE_CARDS_SPACING;
		setCardPositionsOfThePlayers(windowSize.x, windowSize.y, playerCards.cardsInHands[0][0].getCardWidth(), playerCards.cardsInHands[0][0].getCardHeight(), cardsSpacing, tableAndCardsSpacing);
	}
	// TODO - Remove mocked names
	names = { "Caique", "Laert", "Murilo", "Vitor" };
	setPlayerNames(names);
	float textAndTableSpacing = windowSize.y * CALCULATE_TEXT_AND_TABLE_SPACING;
	setNamesPositions(windowSize.x, windowSize.y, textAndTableSpacing, names);
}

void TrucoGame::View::TrucoGameView::setCardPositionsOfThePlayers(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing) {

	float halfScreenWidth = screenWidth / 2;
	float halfScreenHeight = screenHeight / 2;
	float halfCardWidth = cardWidth / 2;

	std::vector<Vector2f> cardsPositions;

	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth - cardsSpacing - cardWidth, cardAndTableSpacing));
	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth, cardAndTableSpacing));
	cardsPositions.push_back(Vector2f(halfScreenWidth + halfCardWidth + cardsSpacing, cardAndTableSpacing));
	players[0]->setCardPositions(cardsPositions);

	cardsPositions.clear();

	cardsPositions.push_back(Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCardWidth - cardsSpacing - cardWidth));
	cardsPositions.push_back(Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCardWidth));
	cardsPositions.push_back(Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight + halfCardWidth + cardsSpacing));
	players[1]->setCardPositions(cardsPositions);


	cardsPositions.clear();

	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth - cardsSpacing - cardWidth + cardWidth, screenHeight - cardAndTableSpacing - cardHeight));
	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth + cardWidth, screenHeight - cardAndTableSpacing - cardHeight));
	cardsPositions.push_back(Vector2f(halfScreenWidth + halfCardWidth + cardsSpacing + cardWidth, screenHeight - cardAndTableSpacing - cardHeight));
	players[2]->setCardPositions(cardsPositions);


	cardsPositions.clear();

	cardsPositions.push_back(Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCardWidth - cardsSpacing - cardWidth));
	cardsPositions.push_back(Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCardWidth));
	cardsPositions.push_back(Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight + halfCardWidth + cardsSpacing));
	players[3]->setCardPositions(cardsPositions);
}

void TrucoGame::View::TrucoGameView::setNamesPositions(float screenWidth, float screenHeight, float textAndTableSpacing, std::vector<std::string>& names)
{
	float halfScreenWidth = screenWidth / 2;
	float halfScreenHeight = screenHeight / 2;
	float halfTextWidth;

	size_t playerIndex = 0;
	PlayerView* player = players[playerIndex];
	player->setPlayerName(names[playerIndex]);
	halfTextWidth = player->getHalfTextWidth(playerIndex);
	player->setNamePosition(Vector2f(halfScreenWidth - halfTextWidth, textAndTableSpacing));

	playerIndex = 1;
	player = players[playerIndex];
	halfTextWidth = player->getHalfTextWidth(playerIndex);
	player->setNamePosition(Vector2f(textAndTableSpacing, halfScreenHeight + halfTextWidth));
	player->setNameRotation(-90.0f);

	playerIndex = 2;
	player = players[playerIndex];
	halfTextWidth = player->getHalfTextWidth(playerIndex);
	float textHeight = player->getTextHeight(playerIndex);
	player->setNamePosition(Vector2f(halfScreenWidth - halfTextWidth, screenHeight - textAndTableSpacing - textHeight - 5));

	playerIndex = 3;
	player = players[playerIndex];
	halfTextWidth = player->getHalfTextWidth(playerIndex);
	player->setNamePosition(Vector2f(screenWidth - textAndTableSpacing, halfScreenHeight - halfTextWidth));
	player->setNameRotation(90.0f);
}

void TrucoGame::View::TrucoGameView::drawScore(GraphicManager* pGraphicManager)
{
	pGraphicManager->drawElement(scoreView.getScoreRectangle());
	pGraphicManager->drawElement(scoreView.getRectangleDivWidth());
	pGraphicManager->drawElement(scoreView.getRectangleDivHeight());

	for (int i = 0; i < 3; i++) {
		pGraphicManager->drawElement(scoreView.getOurCircles(i));
		pGraphicManager->drawElement(scoreView.getTheirCircles(i));
	}

	pGraphicManager->drawElement(scoreView.getRoundScoreText());
	pGraphicManager->drawElement(scoreView.getWeText());
	pGraphicManager->drawElement(scoreView.getTheyText());
}

void TrucoGame::View::TrucoGameView::drawCardsOnTheTable(GraphicManager* pGraphicManager)
{
	for (size_t player = 0; player < NUM_PLAYERS; player++) {
		for (size_t card = 0; card < CARDS_IN_HAND; card++) {
			pGraphicManager->drawElement(playerCards.cardsInHands[player][card]);
		}
	}
}

void TrucoGame::View::TrucoGameView::drawPlayerNames(GraphicManager* pGraphicManager)
{
	for (size_t playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++) {
		pGraphicManager->drawElement(players[playerIndex]->getPlayerName());
	}
}

void TrucoGame::View::TrucoGameView::distributeCardsToPlayers()
{
	std::vector<std::thread*> animationThreads;

	for (size_t player = 0; player < NUM_PLAYERS; player++) {
		for (size_t card = 0; card < CARDS_IN_HAND; card++) {
			CardView* cardView = &playerCards.cardsInHands[player][card];
			if (player == 0) {
				animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::moveSpriteTo, std::ref(*cardView), players[player]->getCardPosition(card), animationSpeed));
			}
			else if (player == 2) {
				std::string newTexturePath = "../../../../TrucoGame/resources/images/cards/Clubs/Ace.png";

				animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::moveAndFlipCardTurnedFaceUpTo,
					std::ref(*cardView), playerCards.getCardTexture(player, card), newTexturePath, players[player]->getCardPosition(card), cardView->getRotation(), animationSpeed, cardScale));
			}
			else {
				animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(*cardView), players[player]->getCardPosition(card), 90.0f, animationSpeed));
			}
		}
	}

	for (std::thread* t : animationThreads) {
		t->detach();
		delete t;
	}
}

TrucoGame::View::TrucoGameView::TrucoGameView(const Vector2f windowSize, const float cardScale, Vector2f& initialDeckPosition) :
	tableView(Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)), initialDeckPosition, cardScale),
	playerCards(NUM_PLAYERS, CARDS_IN_HAND, initialDeckPosition, cardScale),
	scoreView(windowSize)
{
	this->cardScale = cardScale;
	this->animationSpeed = cardScale * CALCULATE_ANIMATION_SPEED;
	initialize(windowSize);
}


TrucoGame::View::TrucoGameView::~TrucoGameView()
{
	for (PlayerView* player : players) {
		delete player;
	}
}

void TrucoGame::View::TrucoGameView::drawElementsOnTheWindow(GraphicManager* pGraphicManager, std::shared_ptr<bool> firstTimeFlag)
{
	if (pGraphicManager) {
		pGraphicManager->drawElement(tableView.getTableCloth());

		if (*firstTimeFlag == true) {
			*firstTimeFlag = false;
			distributeCardsToPlayers();
			tableView.moveDeckAndTurnUpCard(cardScale, animationSpeed);
		}
		drawCardsOnTheTable(pGraphicManager);
		tableView.drawElementsOnTheTable(pGraphicManager);
		drawPlayerNames(pGraphicManager);
		drawScore(pGraphicManager);
	}
}

void TrucoGame::View::TrucoGameView::setPlayerNames(std::vector<std::string> names) {
	for (size_t playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++) {
		players[playerIndex]->setPlayerName(names[playerIndex]);
	}
}