#pragma once
#include "../models/Card.h"
#include "../models/client/ClientGameManager.h"
#include "../views/trucoGameView/TrucoGameView.h"

using namespace TrucoGame::Models;
using namespace TrucoGame::View;

namespace TrucoGame {
	namespace Controller {
		class GMController {
		public:
			GMController(TrucoGameView* gameView, ClientGameManager* gameModel) :
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
		private:
			TrucoGameView* gameView;
			ClientGameManager* gameModel;

			// MODEL CALLS THIS METHODS (events)

			void OnMyTurnStarted(bool canRequestTruco);
			void OnAnotherPlayerPlayed(Card card, int playerId, bool isCovered);

			void OnRoundStarted(Card tableCard, std::vector<Card> handCards);
			void OnElevenHandRoundStart(Card tableCard, std::vector<Card> handCards, std::vector<Card> partnerHandCards);
			void OnIronHandRoundStarted(Card tableCard);

			void OnRoundEnded(int winnerTeamId, int team0Score, int team1Score);

			void OnTurnEnded(int winnerTeamId, int winnerPlayerId);

			void OnTrucoAccepted(int currentStakes);
			void OnTrucoRefused();
			void OnTrucoResquested(int requesterId, int currentStakes);

			void OnGameWon();
			void OnGameLost();

			// VIEWS CALLS THIS METHODS (events, user inputs)

			void UserRequestedTruco();
			void UserSelectedCard(int cardIndex, bool isCovered);
			void UserRespondedTruco(int trucoResult); //0 yes, 1 no, 2 raise
			void UserRespondedElevenHand(bool accepted);


			// Returns: A ID that can be used in the models.
			//   0
			// 1   3
			//   2
			int ModelIdToViewId(int modelId); 

			bool IsMyTeam(int teamId);
		};
	}
}