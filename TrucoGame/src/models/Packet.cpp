#include "../../include/models/Packet.h"
//

void Packet::ToJson(nlohmann::json& j) const {
    j = nlohmann::json{
        {"senderId", senderId},
        {"packetType", packetType},
        {"payload", payload}
    };
}

void Packet::FromJson(const nlohmann::json& j) {
    senderId = static_cast<PacketType>(j["senderId"].get<int>());
    packetType = static_cast<PacketType>(j["packetType"].get<int>());
}