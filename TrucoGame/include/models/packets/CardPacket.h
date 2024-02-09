#pragma once
#include "../Card.h"
#include "Packet.h"

namespace TrucoGame {
    namespace Models {
        class CardPacket : public Packet {
        public:
            Card card;
            int playerId;
            int isCovered;

        public:
            CardPacket(const nlohmann::json& j) :
                Packet(j),
                card(j["payload"]["card"]),
                playerId(j["payload"]["playerId"].get<int>()),
                isCovered(j["payload"]["isCovered"].get<int>())
            {}

            CardPacket(int playerId, Card card, int isCovered) :
                Packet(PacketType::PlayerCard), 
                card(card), 
                playerId(playerId),
                isCovered(isCovered)
            {
                ToJson(payload);
            }

            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["playerId"] = playerId;
                card.ToJson(j["payload"]["card"]);
                j["payload"]["isCovered"] = isCovered;
            }
        };
    }
}
