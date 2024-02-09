#pragma once
#include "Packet.h"

namespace TrucoGame {
    namespace Models {

        class EndTurnPacket : public Packet {
        public:
            int winnerTeamId;
            int winnerPlayerId;

        public:
            EndTurnPacket(const nlohmann::json& j) :
                Packet(j),
                winnerTeamId(j["payload"]["winnerTeamId"].get<int>()),
                winnerPlayerId(j["payload"]["winnerPlayerId"].get<int>())
            {}

            EndTurnPacket(int winnerTeamId, int winnerPlayerId) :
                Packet(PacketType::EndTurn),
                winnerTeamId(winnerTeamId),
                winnerPlayerId(winnerPlayerId)
            {
                ToJson(payload);
            }

            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["winnerTeamId"] = winnerTeamId;
                j["payload"]["winnerPlayerId"] = winnerPlayerId;
            }
        };
    }
}