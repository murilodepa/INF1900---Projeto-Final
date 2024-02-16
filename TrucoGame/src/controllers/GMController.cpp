#include "..\..\include\controllers\GMController.h"
#include "../../include/views/utils/StatesView.h"
#include "../../include/views/utils/MutexView.h"

namespace TrucoGame {
	namespace Controller {

		// ---------------------------
		// MODEL -> CONTROLLER -> VIEW
		// ---------------------------

		GMController::GMController(TrucoGameView* gameView, ClientGameManager* gameModel) :
			gameView(gameView),
			gameModel(gameModel)
		{
			gameModel->myTurnStarted = [this](bool canRequestTruco) { OnMyTurnStarted(canRequestTruco); };
			gameModel->anotherPlayerPlayed = [this](Card card, int playerId, bool isCovered) { OnAnotherPlayerPlayed(card, playerId, isCovered); };
			gameModel->roundStarted = [this](Card tableCard, std::vector<Card> handCards) { OnRoundStarted(tableCard, handCards); };
			gameModel->elevenHandRoundStarted = [this](Card tableCard, std::vector<Card> handCards, std::vector<Card> partnerHandCards) { OnElevenHandRoundStart(tableCard, handCards, partnerHandCards); };
			gameModel->ironHandRoundStarted = [this](Card tableCard) { OnIronHandRoundStarted(tableCard); };
			gameModel->roundEnded = [this](int winnerTeamId, int team0Score, int team1Score) { OnRoundEnded(winnerTeamId, team0Score, team1Score); };
			gameModel->turnEnded = [this](int winnerTeamId, int winnerPlayerId) { OnTurnEnded(winnerTeamId, winnerPlayerId); };
			gameModel->trucoAccepted = [this](int currentStakes) { OnTrucoAccepted(currentStakes); };
			gameModel->trucoRefused = [this]() { OnTrucoRefused(); };
			gameModel->trucoRequested = [this](int requesterId, int currentStakes) { OnTrucoResquested(requesterId, currentStakes); };
			gameModel->gameWon = [this]() { OnGameWon(); };
			gameModel->gameLost = [this]() { OnGameLost(); };

			gameView->userSelectCard = [this](int index, bool covered) { UserSelectedCard(index, covered); };
			gameView->trucoEventHandler = [this]() { UserRequestedTruco(); };
		}

		void GMController::OnMyTurnStarted(bool canRequestTruco){
			// TODO: enable card buttons and truco button if needed
			gameView->notifyPlayer("Sua vez!");

			isPlayerTurnToPlayMutex.lock();
			isPlayerTurnToPlayState = IsPlayerTurnToPlayState::PlayerTurn;
			isPlayerTurnToPlayMutex.unlock();

			checkTrucoRequestMutex.lock();
			checkTrucoRequestState = canRequestTruco ? CheckTrucoRequestState::CAN_TRUCO_REQUEST : CheckTrucoRequestState::CANNOT_TRUCO_REQUEST;
			checkTrucoRequestMutex.unlock();
		}

		void GMController::OnAnotherPlayerPlayed(Card card, int playerId, bool isCovered) {
			// Blocking wait state
			
			while (true) 
			{
				roundMutex.lock();
				if(roundState == RoundState::RoundRunning) 
				{
					roundMutex.unlock();
					break;
				}
				roundMutex.unlock();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			// Blocking wait state
			while (true)
			{
				turnMutex.lock();
				if (turnState == TurnState::TurnRunning)
				{
					turnMutex.unlock();
					break;
				}
				turnMutex.unlock();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			
			int viewPlayerId = ModelIdToViewId(playerId);

			std::string texturePath;
			if (!isCovered) {
				CardStruct cardStruct = CardIdToCardView(card);
				std::string texturePath = UtilsView::findTexturePathByNumberAndSuit(cardStruct);
				gameView->setCardToDiscard(texturePath, isCovered, viewPlayerId, currentTurn);
			}
			else {
				gameView->setCardToDiscard(isCovered, viewPlayerId, currentTurn);
			}

			discardCardMutex.lock();
			discardCardState = DiscardCardState::DiscardCard;
			discardCardMutex.unlock();
			
			//std::string texturePathToturnedFaceUpCard = UtilsView::findTexturePathByNumberAndSuit(cardStruct);
			// TODO: show other card player on the screen
		}

		void GMController::OnRoundStarted(Card tableCard, std::vector<Card> handCards){
			// TODO: show hand cards and table card (keep card buttons disabled)
			roundScoreMutex.lock();
			gameView->scoreView.changeRoundScoreText(int(1));
			roundScoreMutex.unlock();

			CardStruct cardStruct = CardIdToCardView(tableCard);
			std::string texturePathToturnedFaceUpCard = UtilsView::findTexturePathByNumberAndSuit(cardStruct);
			gameView->setTexturePathToturnedFaceUpCard(texturePathToturnedFaceUpCard);

			std::vector<std::string> texturePathToMainPlayerCards;
			for (Card& card : handCards)
			{
				CardStruct cardStruct = CardIdToCardView(card);
				texturePathToMainPlayerCards.emplace_back(UtilsView::findTexturePathByNumberAndSuit(cardStruct));
			}

			gameView->setTexturePathToMainPlayerCards(texturePathToMainPlayerCards);


			trucoRoundMutex.lock();
			if (trucoRoundState != TrucoRoundState::IronHandRound)
			{
				trucoRoundState = TrucoRoundState::NormalRound;
			}
			trucoRoundMutex.unlock();
			
			roundMutex.lock();
			if (roundState == RoundState::RoundReadyToStart)
			{
				distributeCardsToPlayersMutex.lock();
				distributeCardsToPlayersState = DistributeCardsToPlayersState::Distribute;
				distributeCardsToPlayersMutex.unlock();
				roundState = RoundState::RoundRunning;
				turnState = TurnState::TurnRunning;
			}
			//if (roundAndTurnState != RoundAndTurnState::RoundEnded) {
			//	roundAndTurnState = RoundAndTurnState::RoundAndTurnRunning;
			//}
			roundMutex.unlock();
		}
		void GMController::OnElevenHandRoundStart(Card tableCard, std::vector<Card> handCards, std::vector<Card> partnerHandCards){
			// TODO: show partner cards, show hand cards (keep card buttons disabled)
			// and show [yes, no] menu: where the response should somehow call for UserRespondedElevenHand

			gameView->notifyPlayer("Mão de onze");
			std::vector<std::string> texturePathToCards;
			for (Card& card : handCards)
			{
				CardStruct cardStruct = CardIdToCardView(card);
				texturePathToCards.emplace_back(UtilsView::findTexturePathByNumberAndSuit(cardStruct));
			}
			gameView->setTexturePathToMainPlayerCards(texturePathToCards);
			texturePathToCards.clear();
			for (Card& card : partnerHandCards)
			{
				CardStruct cardStruct = CardIdToCardView(card);
				texturePathToCards.emplace_back(UtilsView::findTexturePathByNumberAndSuit(cardStruct));
			}
			gameView->setTexturePathToPartnerHandCards(texturePathToCards);
			
			trucoRoundMutex.lock();
			trucoRoundState = TrucoRoundState::ElevenHandRound;
			trucoRoundMutex.unlock();

			distributeCardsToPlayersMutex.lock();
			distributeCardsToPlayersState = DistributeCardsToPlayersState::Distribute;
			distributeCardsToPlayersMutex.unlock();

			bool result = gameView->tableView.elevenHandReceived();
			if (result) {
				gameView->coverPartnerHandCardsInElevenHandRound();
			}
			UserRespondedElevenHand(result);
		}
		void GMController::OnIronHandRoundStarted(Card tableCard){
			// TODO: just show table card (keep card buttons disabled)
			trucoRoundMutex.lock();
			trucoRoundState = TrucoRoundState::IronHandRound;
			trucoRoundMutex.unlock();
		}

		void GMController::OnRoundEnded(int winnerTeamId, int team0Score, int team1Score){
			if (IsMyTeam(winnerTeamId)) {
				gameView->notifyPlayer("Vencemos essa rodada!");
			}
			else {
				gameView->notifyPlayer("Perdemos essa rodada.");
			}



			gameScoreMutex.lock();
			gameView->scoreView.changeGameScoreText(IsMyTeam(0) ? team0Score : team1Score, IsMyTeam(1) ? team0Score : team1Score);
			gameScoreMutex.unlock();

			roundMutex.lock();
			roundState = RoundState::RoundEnded;
			roundMutex.unlock();
			
			std::chrono::seconds sleepDuration(2);
			std::this_thread::sleep_for(sleepDuration);

			this->currentTurn = 0;
			gameScoreMutex.lock(); gameView->scoreView.resetScoreColor();
			gameScoreMutex.unlock();
		}

		void GMController::OnTurnEnded(int winnerTeamId, int winnerPlayerId){

			turnMutex.lock();
			turnState = TurnState::TurnEnded;
			turnMutex.unlock();

			if (winnerTeamId == -1) {
				gameScoreMutex.lock();
				gameView->scoreView.updateScoreColor(currentTurn, int(TurnResult::DRAW));
				gameScoreMutex.unlock();
			}
			else if (IsMyTeam(winnerTeamId)) {
				gameScoreMutex.lock();
				gameView->scoreView.updateScoreColor(currentTurn, int(TurnResult::WIN));
				gameScoreMutex.unlock();
			}
			else {
				gameScoreMutex.lock();
				gameView->scoreView.updateScoreColor(currentTurn, int(TurnResult::LOSS));
				gameScoreMutex.unlock();
			}
			this->currentTurn++;

			//std::chrono::seconds sleepDuration(5);
			//std::this_thread::sleep_for(sleepDuration);
			//scoreView.updateScoreColor();

			// TODO: update score on the screen (the circles) and clear cards from table to the next turn
		}

		void GMController::OnTrucoAccepted(int currentStakes){
			// TODO: update stakes on the screen
			gameView->notifyPlayer("Truco aceito");

			roundScoreMutex.lock();
			gameView->scoreView.changeRoundScoreText(int(currentStakes));
			roundScoreMutex.unlock();
		}
		void GMController::OnTrucoRefused(){
			gameView->notifyPlayer("Truco recusado");
		}
		void GMController::OnTrucoResquested(int requesterId, int currentStakes){
			// TODO: show popup on the screen to responde [yes = 0, no = 1, raise = 2]
			// where the response should somehow call for UserRespondedTruco
			roundScoreMutex.lock();
			gameView->scoreView.changeRoundScoreText(int(currentStakes));
			roundScoreMutex.unlock();
			int result = gameView->tableView.trucoReceived(currentStakes);
			UserRespondedTruco(result);
		}

		void GMController::OnGameWon(){
			gameView->notifyPlayer("Você venceu!");
		}
		void GMController::OnGameLost(){
			gameView->notifyPlayer("Você perdeu!");
		}

		// ---------------------------
		// VIEW -> CONTROLLER -> MODEL
		// ---------------------------

		void GMController::UserRequestedTruco() {
			gameView->notifyPlayer("TRUCO!");
			gameModel->RequestTruco();
		}
		void GMController::UserSelectedCard(int cardIndex, bool isCovered) {
			gameModel->PlayCard(cardIndex, isCovered);
		}
		void GMController::UserRespondedTruco(int trucoResult) {
			gameModel->RespondTrucoRequest(trucoResult);
		}
		void GMController::UserRespondedElevenHand(bool accepted) {
			gameModel->RespondElevenHand(accepted);
		}


		int GMController::ModelIdToViewId(int modelId)
		{
			int myId = gameModel->player->playerId;
			return ((modelId + 2) - myId) % 4;
		}

		bool GMController::IsMyTeam(int teamId) {
			return (gameModel->player->playerId % 2) == teamId;
		}

		CardStruct GMController::CardIdToCardView(Card card)
		{
			CardStruct cardStruct;
			cardStruct.rank = CardRank(card.getNumber());
			cardStruct.suit = CardSuit(card.getSuit());
			return cardStruct;
		}
	}
}

