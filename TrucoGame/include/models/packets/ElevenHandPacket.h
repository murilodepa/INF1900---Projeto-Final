#pragma once
#include "../Card.h"
#include "Packet.h"
#include <vector>

namespace TrucoGame {
    namespace Models {  
        class ElevenHandPacket : public Packet {
        public:
            Card tableCard;
            std::vector<Card> handCards;
            std::vector<Card> partnerHand;

        public:
            ElevenHandPacket(const nlohmann::json& j):
                Packet(j),
                tableCard(j["payload"]["tableCard"])
            {
                for (const auto& cardJson : j["payload"]["handCards"]) {
                    handCards.push_back(Card::FromJson(cardJson));
                }
                for (const auto& cardJson : j["payload"]["partnerHand"]) {
                    partnerHand.push_back(Card::FromJson(cardJson));
                }
            }
            ElevenHandPacket(Card tablecard, std::vector<Card> handCards, std::vector<Card> partnerHand):
                Packet(PacketType::ElevenHand),
                tableCard(tablecard),
                handCards(handCards),
                partnerHand(partnerHand)

            {
                ToJson(payload);
            }
            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                tableCard.ToJson(j["payload"]["tableCard"]);
                for (const auto& card : handCards) {
                    nlohmann::json cardJson;
                    card.ToJson(cardJson);
                    j["payload"]["handCards"].push_back(cardJson);
                }
                for (const auto& card : partnerHand) {
                    nlohmann::json cardJson;
                    card.ToJson(cardJson);
                    j["payload"]["partnerHand"].push_back(cardJson);
                }
            }
        };
    }
}