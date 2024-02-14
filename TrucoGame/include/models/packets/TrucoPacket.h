#pragma once
#include "Packet.h"

namespace TrucoGame {
    namespace Models {
        enum TrucoResult {
            Yes,
            No,
            Raise
        };

        class TrucoPacket : public Packet {
        public:
            int requesterId;
            int responseTeamId;
            TrucoResult result;

        public:
            TrucoPacket(const nlohmann::json& j) :
                Packet(j),
                requesterId(j["payload"]["requesterId"].get<int>()),
                responseTeamId(j["payload"]["responseTeamId"].get<int>()),
                result(static_cast<TrucoResult>(j["payload"]["result"].get<int>()))
            {
            }

            TrucoPacket(int requesterId, int responseTeamId, TrucoResult result) :
                Packet(PacketType::Truco),
                requesterId(requesterId),
                responseTeamId(responseTeamId),
                result(result)
            {
                ToJson(payload);
            }

            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["requesterId"] = requesterId;
                j["payload"]["responseTeamId"] = responseTeamId;
                j["payload"]["result"] = result;
            }
        };
    }
}