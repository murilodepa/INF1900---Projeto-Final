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

enum class TrucoRoundState {
    NormalRound,
    ElevenHandRound,
    IronHandRound
};
extern TrucoRoundState trucoRoundState;

extern std::vector<sf::Sprite*> playersCardsOnTheTable;
#endif // STATE_VIEW_H

