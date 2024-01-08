#pragma once
#include <nlohmann/json.hpp>
//#include "Card.h"

enum PacketType {
    StartGame,
    CardPckt,
};

class Packet {
public:
    Packet() {}
    Packet(PacketType type) : packetType(type) {}

    int senderId;
    PacketType packetType;
    std::string payload;

    virtual void ToJson(nlohmann::json& j) const;
    virtual void FromJson(const nlohmann::json& j);
};
