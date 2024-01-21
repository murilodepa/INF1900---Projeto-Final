#include "../../include/models/Score.h"

namespace TrucoGame {
    namespace Models {

        Score::Score() {
            team0 = 0;
            team1 = 1;
            stakes = 1;
        }

        int Score::getStakes() { return stakes; }

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

        void Score::updateScore(int winnerTeamId) 
        {
            if (winnerTeamId == 0)
                team0 += stakes;
            else if (winnerTeamId == 1)
                team1 += stakes;
        }

        void Score::resetScore() {
            team0 = 0;
            team1 = 0;
        }

        void Score::resetStakes() {
            stakes = 1;
        }

    }
}