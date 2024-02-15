#ifndef MUTEX_VIEW_H
#define MUTEX_VIEW_H

#include <mutex>

extern std::mutex uIThreadMutex;
extern std::mutex distributeCardsToPlayersMutex;
extern std::mutex isPlayerTurnToPlayMutex;
extern std::mutex isRoundTurnOrDiscartMutex;
extern std::mutex cardMutex;
extern std::mutex playerIdMutex;
extern std::mutex cardStructMutex;
#endif // MUTEX_VIEW_H
