#pragma once
#include "Packet.h"

namespace TrucoGame {
    namespace Models {

        class EndRoundPacket : public Packet {
        public:
            int winnerTeamId;
            int stakes;
            int team0Score;
            int team1Score;

        public:
            EndRoundPacket(const nlohmann::json& j) :
                Packet(j),
                winnerTeamId(j["payload"]["winnerTeamId"].get<int>()),
                stakes(j["payload"]["stakes"].get<int>()),
                team0Score(j["payload"]["team0Score"].get<int>()),
                team1Score(j["payload"]["team1Score"].get<int>())
            {
            }
            EndRoundPacket(int winnerTeamId, int stakes, int team0Score, int team1Score) :
                Packet(PacketType::EndRound),
                winnerTeamId(winnerTeamId),
                stakes(stakes),
                team0Score(team0Score),
                team1Score(team1Score)
            {
                ToJson(payload);
            }
            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["winnerTeamId"] = winnerTeamId;
                j["payload"]["stakes"] = stakes;
                j["payload"]["team0Score"] = team0Score;
                j["payload"]["team1Score"] = team1Score;
            }
        };
    }
}