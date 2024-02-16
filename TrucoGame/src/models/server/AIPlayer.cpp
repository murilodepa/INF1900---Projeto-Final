#include "../../../include/models/server/AIPlayer.h"
#include "../../../include/models/packets/StartRoundPacket.h"
#include "../../../include/models/packets/EndRoundPacket.h"
#include "../../../include/models/packets/PlayerPlayPacket.h"
#include "../../../include/models/packets/ElevenHandResponsePacket.h"
#include "../../../include/models/packets/ElevenHandPacket.h"
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
                player.setHand(startRoundPacket.handCards);
                break;
            }
            case PlayerPlay:
            {
                PlayerPlayPacket playerPlayPacket(packet->payload);

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(0, 100);
                int randomIndex = distrib(gen);

                if (randomIndex < chanceOfRequestingTruco && playerPlayPacket.canRequestTruco)
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
            case ElevenHand:
            {
                ElevenHandPacket elevenHandPacket(packet->payload);
                player.setHand(elevenHandPacket.handCards);
                nextPlay = new ElevenHandResponsePacket(1);
                break;
            }
            default:
                std::cout << "Received invalid packet (" << packet->packetType << ")" << std::endl;
                break;
            }
            return ErrorCode::Success;

        }

        Packet* AIPlayer::WaitForPacket() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(2, 4);
            int randomIndex = distrib(gen);
            std::chrono::seconds sleepDuration(randomIndex);
            std::this_thread::sleep_for(sleepDuration);
            return nextPlay;
        }
    }
}