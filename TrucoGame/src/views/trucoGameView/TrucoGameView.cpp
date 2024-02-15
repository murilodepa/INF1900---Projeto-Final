#include "../../../include/views/trucoGameView/TrucoGameView.h"
#include "../../../include/views/trucoGameView/Animator.h"
#include "../../../include/views/utils/MutexView.h"
#include "../../../include/views/utils/StatesView.h"

#include <thread>

void TrucoGame::View::TrucoGameView::initialize(const std::vector<std::string>& playerNames)
{
	for (size_t playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++) {
		PlayerView* player = new PlayerView(CARDS_IN_HAND, windowSize.y, playerNames[playerIndex]);
		players.push_back(player);
	}

	cardButtons.resize(CARDS_IN_HAND);
	positionToDiscardCards.resize(NUM_PLAYERS);
	texturePathToMainPlayerCards.resize(CARDS_IN_HAND);
	//playersCardsOnTable.resize(NUM_PLAYERS);

	if (playerCards.cardsInHands != nullptr) {
		float tableAndCardsSpacing = windowSize.y * CALCULATE_TABLE_AND_CARDS_SPACING;
		float cardsSpacing = windowSize.x * CALCULATE_CARDS_SPACING;
		setCardPositionsOfThePlayers(windowSize.x, windowSize.y, playerCards.cardsInHands[0][0].getCardWidth(), playerCards.cardsInHands[0][0].getCardHeight(), cardsSpacing, tableAndCardsSpacing);
	}
	// TODO - Remove mocked names
	//names = { "Caique", "Laert", "Murilo", "Vitor" };
	float textAndTableSpacing = windowSize.y * CALCULATE_TEXT_AND_TABLE_SPACING;
	setNamesPositions(windowSize.x, windowSize.y, textAndTableSpacing);
	setPositionToDiscardCards();
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

void TrucoGame::View::TrucoGameView::setNamesPositions(float screenWidth, float screenHeight, float textAndTableSpacing)
{
	float halfScreenWidth = screenWidth / 2;
	float halfScreenHeight = screenHeight / 2;
	float halfTextWidth;

	size_t playerIndex = 0;
	PlayerView* player = players[playerIndex];
	halfTextWidth = player->playerName->getHalfTextWidth();
	player->setNamePosition(Vector2f(halfScreenWidth - halfTextWidth, textAndTableSpacing));

	playerIndex = 1;
	player = players[playerIndex];
	halfTextWidth = player->playerName->getHalfTextWidth();
	player->setNamePosition(Vector2f(textAndTableSpacing, halfScreenHeight + halfTextWidth));
	player->setNameRotation(-90.0f);

	playerIndex = 2;
	player = players[playerIndex];
	halfTextWidth = player->playerName->getHalfTextWidth();
	float textHeight = player->playerName->getTextHeight();
	player->setNamePosition(Vector2f(halfScreenWidth - halfTextWidth, screenHeight - textAndTableSpacing - textHeight - 0.3f * textHeight));

	playerIndex = 3;
	player = players[playerIndex];
	halfTextWidth = player->playerName->getHalfTextWidth();
	player->setNamePosition(Vector2f(screenWidth - textAndTableSpacing, halfScreenHeight - halfTextWidth));
	player->setNameRotation(90.0f);
}

void TrucoGame::View::TrucoGameView::setPositionToDiscardCards() {
	//Vector2f(0.70f * windowSize.x, 0.63f * windowSize.y);
	positionToDiscardCards[0] = Vector2f(0.35f * windowSize.x, 0.42f * windowSize.y); // front
	positionToDiscardCards[1] = Vector2f(0.35f * windowSize.x, 0.65f * windowSize.y); // left
	positionToDiscardCards[2] = Vector2f(0.75f * windowSize.x, 0.65f * windowSize.y); //Main player
	positionToDiscardCards[3] = Vector2f(0.75f * windowSize.x, 0.42f * windowSize.y); // right
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
			uIThreadMutex.lock();
			pGraphicManager->drawElement(playerCards.cardsInHands[player][card]);
			uIThreadMutex.unlock();
		}
	}
}

void TrucoGame::View::TrucoGameView::drawPlayerNames(GraphicManager* pGraphicManager)
{
	for (size_t playerIndex = 0; playerIndex < NUM_PLAYERS; playerIndex++) {
		pGraphicManager->drawElement(players[playerIndex]->getPlayerName());
	}
}


void TrucoGame::View::TrucoGameView::checkIftheCardHasBeenDiscardedAndDraw(GraphicManager* pGraphicManager, Vector2f& mousePosView)
{
	for (size_t card = 0; card < CARDS_IN_HAND; card++) {
		CardButton* cardButton = cardButtons[card];
		if (cardButton->getAreCardsInTheHandsOfThePlayer()) {
			cardButton->update(mousePosView);
			pGraphicManager->drawElement(*cardButton);
		}
		if (!cardButtons[0]->getAreCardsInTheHandsOfThePlayer() && !cardButtons[1]->getAreCardsInTheHandsOfThePlayer() && !cardButtons[2]->getAreCardsInTheHandsOfThePlayer()) {
			cardButtons[0]->setAreCardsInTheHandsOfThePlayer(true);
			testDiscartCards();
		}
	}
}


void TrucoGame::View::TrucoGameView::distributeCardsToPlayers()
{
	if (playerCards.cardsInHands != nullptr) {
		float tableAndCardsSpacing = windowSize.y * CALCULATE_TABLE_AND_CARDS_SPACING;
		float cardsSpacing = windowSize.x * CALCULATE_CARDS_SPACING;
		setCardPositionsOfThePlayers(windowSize.x, windowSize.y, playerCards.cardsInHands[0][0].getCardWidth(), playerCards.cardsInHands[0][0].getCardHeight(), cardsSpacing, tableAndCardsSpacing);
	}
	std::vector<std::thread*> animationThreads;

	for (size_t player = 0; player < NUM_PLAYERS; player++) {
		for (size_t card = 0; card < CARDS_IN_HAND; card++) {
			CardView* cardView = &playerCards.cardsInHands[player][card];
			float rotation = cardView->getRotation();
			if (player == 0) {
				animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::moveSpriteTo, std::ref(*cardView), players[player]->getCardPosition(card), animationSpeed));
			}
			else if (player == 2) {
				Texture* cardTexture = playerCards.getCardTexture(player, card);

				Vector2f destinationPosition = players[player]->getCardPosition(card);
				animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::moveAndFlipCardTurnedFaceUpTo,
					std::ref(*cardView), cardTexture, texturePathToMainPlayerCards[card], destinationPosition, animationSpeed, cardScale));
			
				float width = cardView->getCardWidth();

				cardButtons[card] = new CardButton(destinationPosition.x - width, destinationPosition.y, width, cardView->getCardHeight(), COLOR_CARD_HOVER, cardView, windowSize, animationSpeed, positionToDiscardCards[2], cardTexture, card);
				cardButtons[card]->setAreCardsInTheHandsOfThePlayer(true);
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

void TrucoGame::View::TrucoGameView::testDiscartCards()
{
	
	std::vector<std::thread*> animationThreads;

	CardView* cardView = &playerCards.cardsInHands[0][1];
	CardStruct cardStruct;
	cardStruct.rank = CardRank::Ace;
	cardStruct.suit = CardSuit::Hearts;
	playersCardsOnTable.push_back(cardView);
	//discardCard(0, 1, cardStruct);


	cardView = &playerCards.cardsInHands[1][1];
	playersCardsOnTable.push_back(cardView);
	//discardCard(1, 1, cardStruct);


	cardView = &playerCards.cardsInHands[2][1];
	playersCardsOnTable.push_back(cardView);
	//discardCard(2, 1, cardStruct);


	cardView = &playerCards.cardsInHands[3][1];
	playersCardsOnTable.push_back(cardView);
	//discardCard(3, 1, cardStruct);



	for (std::thread* t : animationThreads) {
		t->detach();
		delete t;
	}
}

TrucoGame::View::TrucoGameView::TrucoGameView(const Vector2f windowSize, const float cardScale, Vector2f& initialDeckPosition, const std::vector<std::string>& playerNames) :
	tableView(Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)), initialDeckPosition, cardScale),
	playerCards(NUM_PLAYERS, CARDS_IN_HAND, initialDeckPosition, cardScale),
	scoreView(windowSize)
{
	this->cardScale = cardScale;
	this->animationSpeed = cardScale * CALCULATE_ANIMATION_SPEED;
	this->windowSize = windowSize;
	this->deckPosition = tableView.getDeckPosition();
	this->deckRotation = tableView.getDeckRotation();
	initialize(playerNames);
}


TrucoGame::View::TrucoGameView::~TrucoGameView()
{
	for (PlayerView* player : players) {
		delete player;
	}
}

void TrucoGame::View::TrucoGameView::drawElementsOnTheWindow(GraphicManager* pGraphicManager, std::shared_ptr<bool> firstTimeFlag, Vector2f& mousePosView)
{
	if (pGraphicManager) {
		pGraphicManager->drawElement(tableView.getTableCloth());

		distributeCardsToPlayersMutex.lock();
		if (distributeCardsToPlayersState == DistributeCardsToPlayersState::Distribute) {
			distributeCardsToPlayersState = DistributeCardsToPlayersState::NotDistribute;
			distributeCardsToPlayers();
			tableView.moveDeckAndTurnUpCard(cardScale, animationSpeed, texturePathToturnedFaceUpCard);
		}
		distributeCardsToPlayersMutex.unlock();

		drawCardsOnTheTable(pGraphicManager);
		tableView.drawElementsOnTheTable(pGraphicManager);
		drawPlayerNames(pGraphicManager);
		drawScore(pGraphicManager);
		checkIftheCardHasBeenDiscardedAndDraw(pGraphicManager, mousePosView);

		if (isRoundTurnOrDiscartState == IsRoundTurnOrDiscartState::DiscardCard) {
			isRoundTurnOrDiscartState == IsRoundTurnOrDiscartState::WaitingPlayer;
			discardCard();
		}
	}
}

void TrucoGame::View::TrucoGameView::setTexturePathToMainPlayerCards(std::vector<std::string>& texturePathToMainPlayerCards)
{
	this->texturePathToMainPlayerCards = texturePathToMainPlayerCards;
}

void TrucoGame::View::TrucoGameView::setTexturePathToturnedFaceUpCard(std::string& texturePathToturnedFaceUpCard)
{
	this->texturePathToturnedFaceUpCard = texturePathToturnedFaceUpCard;
}

void TrucoGame::View::TrucoGameView::discardCard()
{
	playerIdMutex.lock();
	size_t player = static_cast<size_t>(playerIdState);
	playerIdMutex.unlock();

	cardStructMutex.lock();
	CardStruct cardStruct = cardStructState;
	cardStructMutex.unlock();

	size_t cardIndex = static_cast<size_t>(cardStruct.index);
	std::string cardTexturePath;


	cardMutex.lock();
	if (cardState == CardState::Covered) {
		cardTexturePath = CARD_BACK_TEXTURE_PATH;
	}
	else {
		cardTexturePath = UtilsView::findTexturePathByNumberAndSuit(cardStruct);
	}
	cardMutex.unlock();
	
	if (player < NUM_PLAYERS && player >= 0 && cardIndex < CARDS_IN_HAND && cardIndex >= 0) {
		CardView* cardView = &playerCards.cardsInHands[player][cardIndex];
		std::thread* animationThread;

		if (player == 3) {
			animationThread = new std::thread(&TrucoGame::View::Animator::animationToDiscardCard, std::ref(*cardView), playerCards.getCardTexture(player, cardIndex), cardTexturePath, positionToDiscardCards[3], animationSpeed, cardScale, 0, playersCardsOnTable, deckPosition, playerCards.cardsInHands, tableView.getCardTurnedFaceUp(), tableView.getDeck());
		}  if (player == 0) {
			animationThread = new std::thread(&TrucoGame::View::Animator::animationToDiscardCard, std::ref(*cardView), playerCards.getCardTexture(player, cardIndex), cardTexturePath, positionToDiscardCards[0], animationSpeed, cardScale, 90, playersCardsOnTable, deckPosition, playerCards.cardsInHands, tableView.getCardTurnedFaceUp(), tableView.getDeck());
		}
		else if (player == 1) {
			Vector2f destinationPosition = Vector2f(positionToDiscardCards[1].x, positionToDiscardCards[1].y + cardView->getCardWidth());
			animationThread = new std::thread(&TrucoGame::View::Animator::animationToDiscardCard, std::ref(*cardView), playerCards.getCardTexture(player, cardIndex), cardTexturePath, destinationPosition, animationSpeed, cardScale, 0, playersCardsOnTable, deckPosition, playerCards.cardsInHands, tableView.getCardTurnedFaceUp(), tableView.getDeck());
		}

		if (player != 2 && player != 0 && player != 1) {
			animationThread->detach();
			delete animationThread;
		}

		tableView.moveTurnUpCardToDeck(cardScale, animationSpeed);
	}
}