#pragma once
#include "../Card.h"
#include "Packet.h"
#include <vector>

namespace TrucoGame {
    namespace Models {  
        class StartRoundPacket : public Packet {
        public:
            Card tableCard;
            std::vector<Card> handCards;

        public:
            StartRoundPacket(const nlohmann::json& j):
                Packet(j),
                tableCard(j["payload"]["tableCard"])
            {
                for (const auto& cardJson : j["payload"]["handCards"]) {
                    handCards.push_back(Card::FromJson(cardJson));
                }
            }
            StartRoundPacket(Card tablecard, std::vector<Card> handCards):
                Packet(PacketType::StartRound),
                tableCard(tablecard),
                handCards(handCards)
            {}
            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                tableCard.ToJson(j["payload"]["tableCard"]);
                for (const auto& card : handCards) {
                    nlohmann::json cardJson;
                    card.ToJson(cardJson);
                    j["payload"]["handCards"].push_back(cardJson);
                }
            }
        };
    }
}