#pragma once


namespace TrucoGame {
    namespace Models {

        class Score {
        private:
            int team0GameScore;
            int team1GameScore;
            int stakes;
            int team0RoundScore;
            int team1RoundScore;
        public:
            Score();
            
            // Retuns stakes: (1, 3, 6, 9, 12)
            int getStakes();
            // Best of three turn score (max is 2)
            int getTeam0RoundScore();
            // Best of three turn score (max is 2)
            int getTeam1RoundScore();
            // Game score (max is 12)
            int getTeam0GameScore();
            // Game score (max is 12)
            int getTeam1GameScore();

            // Returns: ID of the turn winner team or 0 if none won yet.
            int updateTurnScore(int winnerTeamId);
            // Returns: ID of the round winner team or 0 if none won yet.
            int updateRoundScore(int winnerTeamId);

            // 1 -> 3 -> 6 -> 9 -> 12
            void increaseStakes();

            void resetRound();
            void resetGame();
            void resetStakes();
        };
    }
}