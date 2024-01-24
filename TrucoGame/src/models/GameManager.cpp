#include "../../include/models/GameManager.h"

namespace TrucoGame {
    namespace Models {
        void GameManager::playCard(int playerId, int cardIndex, bool isCovered)
        {
            Card* card = players[playerId].hand[cardIndex];
            table.PlaceCard(card, playerId, isCovered);
        }

        void GameManager::endTurn() 
        {
            int turnWinner = table.CalculateWinner();
            int roundWinner = score.updateTurnWon(turnWinner % 2);
            //TODO: clear table cards
            if (roundWinner != -1) 
            {
                endRound(roundWinner);                
            }
        }

        void GameManager::startRound()
        {
            //Give players hand cards
            table.turnedCard = deck.pop();
            score.resetRound();
        }

        void GameManager::endRound(int roundWinner) 
        {
            int gameWinner = score.updateRoundWon(roundWinner);
            //TODO: CleanPlayerCards(); ClearTurnedCard();
            if(gameWinner != -1)
            {
                endGame(gameWinner);
            }
        }

        void GameManager::endGame(int gameWinner)
        {
            //end the game based on the winner
        }
    }
}