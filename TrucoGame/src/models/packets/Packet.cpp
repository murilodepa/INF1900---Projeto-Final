#include "../../../include/models/packets/Packet.h"

namespace TrucoGame {
    namespace Models {
        void Packet::ToJson(nlohmann::json& j) const {
            j = nlohmann::json{
                {"packetType", packetType},
                {"payload", nlohmann::json()}
            };
        }
    }
}