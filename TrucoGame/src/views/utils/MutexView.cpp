#include "../../../include/views/utils/MutexView.h"

std::mutex uIThreadMutex;
std::mutex distributeCardsToPlayersState;
std::mutex distributeCardsToPlayersMutex;
std::mutex isPlayerTurnToPlayMutex;
std::mutex turnMutex;
std::mutex roundMutex;
std::mutex discardCardMutex;
std::mutex cardStructMutex;
std::mutex gameScoreMutex;
std::mutex roundScoreMutex;
std::mutex trucoRoundMutex;
std::mutex changePlayersCardsOnTheTableMutex;
std::mutex checkTrucoRequestMutex;