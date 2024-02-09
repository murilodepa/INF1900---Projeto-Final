#include "../../../include/models/server/AIPlayer.h"
#include "../../../include/models/packets/StartRoundPacket.h"
#include "../../../include/models/packets/EndRoundPacket.h"
#include "../../../include/models/packets/PlayerPlayPacket.h"
#include <nlohmann/json.hpp>
#include <random>

namespace TrucoGame {

    namespace Models {

        ErrorCode AIPlayer::StartListening()
        {
            return ErrorCode::Success;
        }

        void AIPlayer::Listen()
        {

        }

        ErrorCode AIPlayer::Send(Packet* packet)
        {
            switch (packet->packetType)
            {
            case StartRound:
            {   
                StartRoundPacket startRoundPacket(packet->payload);
                player.hand = startRoundPacket.handCards;
                break;
            }
            case PlayerPlay:
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(0, 100);
                int randomIndex = distrib(gen);

                if (randomIndex < chanceOfRequestingTruco)
                {
                    nextPlay = new TrucoPacket(id, (id + 1) % 2, TrucoResult::Raise);
                }
                else
                {
                    //if(randomIndex < chanceOfRandomCard)
                    nextPlay = new CardPacket(id, player.popCardByIndex(0), false);
                }
                
                break;
            }
            case Truco:
            {
                TrucoPacket trucoPacket(packet->payload);
                if (trucoPacket.result == TrucoResult::Yes) {
                    if (trucoPacket.requesterId == id)
                    {
                        nextPlay = new CardPacket(id, player.popCardByIndex(0), false);
                    }
                }
                else
                {
                    if (trucoPacket.responseTeamId == id % 2)
                    {
                        nextPlay = new TrucoPacket(trucoPacket.requesterId, !trucoPacket.responseTeamId, TrucoResult::Yes);
                    }
                }
                break;
            }
            default:
                break;
            }
            return ErrorCode::Success;

        }

        Packet* AIPlayer::WaitForPacket() {
            return nextPlay;
        }
    }
}