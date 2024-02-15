#ifndef STATE_VIEW_H
#define STATE_VIEW_H

#include "CardsEnum.h"

enum class DistributeCardsToPlayersState {
    NotDistribute,
    Distribute
};
extern DistributeCardsToPlayersState distributeCardsToPlayersState;

enum class RoundAndTurnState {
    RoundEnded,
    TurnEnded,
    RoundAndTurnRunning
};
extern RoundAndTurnState roundAndTurnState;

enum class DiscardCardState {
    WaitingPlayer,
    DiscardCard
};
extern DiscardCardState discardCardState;

enum class CardState {
    TurnedUp,
    Covered
};
extern CardState cardState;

enum class PlayerIdState {
    Left = 1,
    Front = 0,
    Right = 3
};
extern PlayerIdState playerIdState;

extern CardStruct cardStructState;

enum class IsPlayerTurnToPlayState {
    NotPlayerTurn,
    PlayerTurn
};
extern IsPlayerTurnToPlayState isPlayerTurnToPlayState;


#endif // STATE_VIEW_H

