#pragma once


namespace TrucoGame {
    namespace Models {

        class Score {
        private:
            int team0GameScore;
            int team1GameScore;
            int stakes;
            int team0TurnsWon;
            int team1TurnsWon;
            bool isRoundDrawn = false;
            int firstTurnWinner = -1;
        public:
            Score();
            
            const int maxStakes = 12;

            // Retuns stakes: (1, 3, 6, 9, 12)
            int getStakes();
            // Best of three turn score (max is 2)
            int getTeam0TurnsWon();
            // Best of three turn score (max is 2)
            int getTeam1TurnsWon();
            // Game score (max is 12)
            int getTeam0GameScore();
            // Game score (max is 12)
            int getTeam1GameScore();

            // Parameters:
            // winnerTeamId: (1 or 0) to winning team or (-1) if draw
            // Returns: ID of the turn winner team or -1 if none won yet.
            int updateTurnWon(int winnerTeamId);
            // Parameters:
            // winnerTeamId: (1 or 0) to winning team or (-1) if draw
            // Returns: ID of the round winner team or -1 if none won yet.
            int updateRoundWon(int winnerTeamId);

            // 1 -> 3 -> 6 -> 9 -> 12
            void increaseStakes();

            void resetRound();
            void resetGame();
        };
    }
}