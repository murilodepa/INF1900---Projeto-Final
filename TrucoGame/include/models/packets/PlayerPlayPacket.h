#pragma once
#include "Packet.h"

namespace TrucoGame {
    namespace Models {

        class PlayerPlayPacket : public Packet {
        public:
            int playerId;
            int canRequestTruco;

        public:
            PlayerPlayPacket(const nlohmann::json& j) :
                Packet(j),
                playerId(j["payload"]["playerId"].get<int>()),
                canRequestTruco(j["payload"]["canRequestTruco"].get<int>())
            {
            }

            PlayerPlayPacket(int playerId, int canRequestTruco) :
                Packet(PacketType::PlayerPlay),
                playerId(playerId),
                canRequestTruco(canRequestTruco)
            {
                ToJson(payload);
            }

            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["playerId"] = playerId;
                j["payload"]["canRequestTruco"] = canRequestTruco;
            }
        };
    }
}