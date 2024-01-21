#pragma once


namespace TrucoGame {
    namespace Models {

        class Score {
        private:
            int team0;
            int team1;
            int stakes;
        public:
            Score();
            int getStakes();
            void updateScore(int winnerTeamId);
            void increaseStakes();
            void resetScore();
            void resetStakes();
        };
    }
}