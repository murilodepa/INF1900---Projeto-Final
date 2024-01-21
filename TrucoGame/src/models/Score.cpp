#include "../../include/models/Score.h"
#include "..\..\include\models\Score.h"

#define POINT_TO_WIN 12

namespace TrucoGame {
    namespace Models {

        Score::Score() {
            resetStakes();
            resetGame();
            resetRound();
        }

        int Score::getStakes() { return stakes; }
        int Score::getTeam0RoundScore() { return team0RoundScore; }
        int Score::getTeam1RoundScore() { return team1RoundScore; }
        int Score::getTeam0GameScore() { return team0GameScore; }
        int Score::getTeam1GameScore() { return team1GameScore; }

        void Score::increaseStakes() 
        {
            if (stakes == 1)
                stakes = 3;
            else if (stakes == 3)
                stakes = 6;
            else if (stakes == 6)
                stakes = 9;
            else if (stakes == 9)
                stakes = 12;
        }

        
        int Score::updateTurnScore(int winnerTeamId)
        {
            if (winnerTeamId == 0)
            {
                team0RoundScore += 1; 
                if (team0RoundScore == 2) //check win round
                    return 0;
            }
            else if (winnerTeamId == 1)
            {
                team1RoundScore += 1;
                if (team1RoundScore == 2) //check win round
                    return 1;
            }
            return 0; //none one
        }

        int Score::updateRoundScore(int winnerTeamId) 
        {
            if (winnerTeamId == 0)
            {
                team0GameScore += 1;
                if (team0GameScore >= POINT_TO_WIN) //check win game
                    return 0;
            }
            else if (winnerTeamId == 1)
            {
                team1GameScore += 1;
                if (team1GameScore >= POINT_TO_WIN) //check win game
                    return 1;
            }
            return 0; //none won
        }

        void Score::resetRound() {
            team0RoundScore = 0;
            team1RoundScore = 0;
        }

        void Score::resetGame() {
            team0GameScore = 0;
            team1GameScore = 0;
        }

        void Score::resetStakes() {
            stakes = 1;
        }

    }
}