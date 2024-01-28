#pragma once
#include "../Card.h"
#include "Packet.h"

namespace TrucoGame {
    namespace Models {
        class CardPacket : public Packet {
        public:
            Card card;
            int playerId;

        public:
            CardPacket(const nlohmann::json& j) :
                Packet(j),
                card(j["payload"]["card"]),
                playerId(j["payload"]["playerId"].get<int>())
            {}

            CardPacket(int playerId, Card card) :
                Packet(PacketType::PlayerCard), 
                card(card), 
                playerId(playerId) 
            {}
            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["playerId"] = playerId;
                card.ToJson(j["payload"]["card"]);
            }
        };
    }
}
