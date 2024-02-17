#ifndef MUTEX_VIEW_H
#define MUTEX_VIEW_H

#include <mutex>

extern std::mutex uIThreadMutex;
extern std::mutex distributeCardsToPlayersMutex;
extern std::mutex isPlayerTurnToPlayMutex;
extern std::mutex turnMutex;
extern std::mutex roundMutex;
extern std::mutex discardCardMutex;
extern std::mutex cardStructMutex;
extern std::mutex gameScoreMutex;
extern std::mutex roundScoreMutex;
extern std::mutex trucoRoundMutex;
extern std::mutex changePlayersCardsOnTheTableMutex;
extern std::mutex checkTrucoRequestMutex;
extern std::mutex setupGameMutex;
extern std::mutex cardIsBeingDiscarded;

#endif // MUTEX_VIEW_H
