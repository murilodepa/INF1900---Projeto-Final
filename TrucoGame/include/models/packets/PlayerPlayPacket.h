#pragma once
#include "Packet.h"

namespace TrucoGame {
    namespace Models {

        class PlayerPlayPacket : public Packet {
        public:
            int playerId;

        public:
            PlayerPlayPacket(const nlohmann::json& j) :
                Packet(j),
                playerId(j["payload"]["playerId"].get<int>())
            {
            }

            PlayerPlayPacket(int playerId) :
                Packet(PacketType::PlayerPlay),
                playerId(playerId)
            {
            }

            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["playerId"] = playerId;
            }
        };
    }
}