#ifndef STATE_VIEW_H
#define STATE_VIEW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "CardsEnum.h"

enum class DistributeCardsToPlayersState {
    NotDistribute,
    Distribute
};
extern DistributeCardsToPlayersState distributeCardsToPlayersState;

enum class TurnState {
    TurnRunning,
    TurnEnded,
    ReturnCardsToDeck,
    DiscardCard
};
extern TurnState turnState;

enum class RoundState {
    RoundReadyToStart,
    RoundEnded,
    RoundRunning,
    DistribuiteCards
};
extern RoundState roundState;

enum class DiscardCardState {
    WaitingPlayer,
    DiscardCard
};
extern DiscardCardState discardCardState;

enum class TurnResult {
    DRAW = 0,
    WIN = 1,
    LOSS = -1
};

extern CardStruct cardStructState;

enum class IsPlayerTurnToPlayState {
    NotPlayerTurn,
    PlayerTurn
};
extern IsPlayerTurnToPlayState isPlayerTurnToPlayState;

enum class TrucoRoundState {
    NormalRound,
    ElevenHandRound,
    IronHandRound
};
extern TrucoRoundState trucoRoundState;

enum class CheckTrucoRequestState {
    CanTrucoRequest,
    CanNotTrucoRequest
};
extern CheckTrucoRequestState checkTrucoRequestState;

enum class CheckSetupGameState {
    SetupGameHasBeenConfigured,
    SetupGameHasNotBeenConfigured
};
extern CheckSetupGameState checkSetupGameState;

extern std::vector<sf::Sprite*> playersCardsOnTheTable;
#endif // STATE_VIEW_H

