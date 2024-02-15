#ifndef STATE_VIEW_H
#define STATE_VIEW_H

#include "CardsEnum.h"

enum class DistributeCardsToPlayersState {
    Distribute,
    NotDistribute
};
extern DistributeCardsToPlayersState distributeCardsToPlayersState;

enum class IsRoundTurnOrDiscartState {
    WaitingPlayer,
    DiscardCard,
    RoundEnded,
    TurnEnded
};
extern IsRoundTurnOrDiscartState isRoundTurnOrDiscartState;

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
    PlayerTurn,
    NotPlayerTurn
};
extern IsPlayerTurnToPlayState isPlayerTurnToPlayState;


#endif // STATE_VIEW_H

