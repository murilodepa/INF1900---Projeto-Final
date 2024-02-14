#include "../../include/models/Score.h"
#include "..\..\include\models\Score.h"
#include <iostream>

namespace TrucoGame {
    namespace Models {

        Score::Score() {
            resetGame();
            resetRound();
        }

        int Score::getStakes() { return stakes; }
        int Score::getTeam0TurnsWon() { return team0TurnsWon; }
        int Score::getTeam1TurnsWon() { return team1TurnsWon; }
        int Score::getTeam0GameScore() { return team0GameScore; }
        int Score::getTeam1GameScore() { return team1GameScore; }

        void Score::increaseStakes() 
        {
            std::cout << "Increasing stakes..." << std::endl;
            std::cout << "Before: " << stakes << std::endl;
            if (stakes == 1)
                stakes = 3;
            else if (stakes == 3)
                stakes = 6;
            else if (stakes == 6)
                stakes = 9;
            else if (stakes == 9)
                stakes = 12;
            std::cout << "After: " << stakes << std::endl;
        }

        
        int Score::updateTurnWon(int winnerTeamId)
        {
            if (team0TurnsWon == 0 && team1TurnsWon == 0)
            {
                firstTurnWinner = winnerTeamId;
            }

            if (winnerTeamId == 0) //TEAM 0 WON TURN
            {
                team0TurnsWon += 1; 
                if (team0TurnsWon == 2 || isRoundDrawn) //check win round
                    return 0;
            }
            else if (winnerTeamId == 1) //TEAM 1 WON TURN
            {
                team1TurnsWon += 1;
                if (team1TurnsWon == 2 || isRoundDrawn) //check win round
                    return 1;
            }
            else if (winnerTeamId == -1) // DRAW TURN
            {
                if (firstTurnWinner != -1) 
                {
                    return firstTurnWinner;
                }

                isRoundDrawn = true;
            }

            return -1; //none won
        }

        int Score::updateRoundWon(int winnerTeamId) 
        {
            if (winnerTeamId == 0)
            {
                team0GameScore += stakes;
                if (team0GameScore >= POINT_TO_WIN) //check win game
                    return 0;
            }
            else if (winnerTeamId == 1)
            {
                team1GameScore += stakes;
                if (team1GameScore >= POINT_TO_WIN) //check win game
                    return 1;
            }
            return -1; //none won
        }

        void Score::resetRound() {
            team0TurnsWon = 0;
            team1TurnsWon = 0;
            isRoundDrawn = false;
            firstTurnWinner = -1;
            stakes = 1;
        }

        void Score::resetGame() {
            team0GameScore = 0;
            team1GameScore = 0;
        }
    }
}