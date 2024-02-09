#pragma once
#include <nlohmann/json.hpp>
//#include "Card.h"

namespace TrucoGame {
    namespace Models {
        enum PacketType {
            StartGame,
            StartRound,
            EndRound,
            EndTurn,
            PlayerPlay,
            PlayerCard,
            Truco,
        };

        class Packet {
        public:
            Packet(PacketType type) : packetType(type) {
            }
            Packet(const nlohmann::json& j):
                payload(j),
                packetType(static_cast<PacketType>(j["packetType"].get<int>()))
            {}

            PacketType packetType;
            nlohmann::json payload;

            virtual void ToJson(nlohmann::json& j) const;
        };
    }
}
