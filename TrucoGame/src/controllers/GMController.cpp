#include "..\..\include\controllers\GMController.h"

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

			//gameView->userRequestedTruco = [this]() { UserRequestedTruco() };
		}

		void GMController::OnMyTurnStarted(bool canRequestTruco){
			// TODO: enable card buttons and truco button if needed
		}
		void GMController::OnAnotherPlayerPlayed(Card card, int playerId, bool isCovered) {
			int viewPlayerId = ModelIdToViewId(playerId);
			// TODO: show other card player on the screen
		}

		void GMController::OnRoundStarted(Card tableCard, std::vector<Card> handCards){
			// TODO: show hand cards and table card (keep card buttons disabled)
		}
		void GMController::OnElevenHandRoundStart(Card tableCard, std::vector<Card> handCards, std::vector<Card> partnerHandCards){
			// TODO: show partner cards, show hand cards (keep card buttons disabled)
			// and show [yes, no] menu: where the response should somehow call for UserRespondedElevenHand

		}
		void GMController::OnIronHandRoundStarted(Card tableCard){
			// TODO: just show table card (keep card buttons disabled)
		}

		void GMController::OnRoundEnded(int winnerTeamId, int team0Score, int team1Score){
			// TODO: update score on the screen, clear cards from hands
		}

		void GMController::OnTurnEnded(int winnerTeamId, int winnerPlayerId){
			// TODO: update score on the screen (the circles) and clear cards from table to the next turn
		}

		void GMController::OnTrucoAccepted(int currentStakes){
			// TODO: update stakes on the screen
		}
		void GMController::OnTrucoRefused(){
			// TODO
		}
		void GMController::OnTrucoResquested(int requesterId, int currentStakes){
			// TODO: show popup on the screen to responde [yes = 0, no = 1, raise = 2]
			// where the response should somehow call for UserRespondedTruco
		}

		void GMController::OnGameWon(){
			// TODO
		}
		void GMController::OnGameLost(){
			// TODO
		}

		// ---------------------------
		// VIEW -> CONTROLLER -> MODEL
		// ---------------------------

		void GMController::UserRequestedTruco() {
			// TODO: send truco packet to server
		}
		void GMController::UserSelectedCard(int cardIndex, bool isCovered) {
			// TODO: send card packet to server
			// disable card button
		}
		void GMController::UserRespondedTruco(int trucoResult) {
			// TODO: send truco packet with the response to server
		}
		void GMController::UserRespondedElevenHand(bool accepted) {
			// TODO: send eleven hand response packet to the server
		}


		int GMController::ModelIdToViewId(int modelId)
		{
			int myId = gameModel->player->playerId;
			return ((modelId + 2) - myId) % 4;
		}

		bool GMController::IsMyTeam(int teamId) {
			return (gameModel->player->playerId % 2) == teamId;
		}
	}
}

