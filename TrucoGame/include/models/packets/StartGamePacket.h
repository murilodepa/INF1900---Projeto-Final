#pragma once
#include "Packet.h"

namespace TrucoGame {
    namespace Models {

        class StartGamePacket : public Packet {
        public:
            int playerId;
            int teamId;

        public:
            StartGamePacket(const nlohmann::json& j) :
                Packet(j),
                playerId(j["payload"]["playerId"].get<int>()),
                teamId(j["payload"]["teamId"].get<int>())
            {
            }

            StartGamePacket(int playerId, int teamId) :
                Packet(PacketType::StartGame),
                playerId(playerId),
                teamId(teamId)
            {
            }

            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["playerId"] = playerId;
                j["payload"]["teamId"] = teamId;
            }
        };
    }
}