#pragma once
#include "Packet.h"

namespace TrucoGame {
    namespace Models {

        class ElevenHandResponsePacket : public Packet {
        public:
            int response;

        public:
            ElevenHandResponsePacket(const nlohmann::json& j) :
                Packet(j),
                response(j["payload"]["response"].get<int>())
            {
            }

            ElevenHandResponsePacket(int response) :
                Packet(PacketType::ElevenHandResponse),
                response(response)
            {
                ToJson(payload);
            }

            void ToJson(nlohmann::json& j) const override {
                Packet::ToJson(j);
                j["payload"]["response"] = response;
            }
        };
    }
}