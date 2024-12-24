#ifndef CHRONOS_PACKETS_H
#define CHRONOS_PACKETS_H

#include <cstdint>
#include <string>
#include <vector>

typedef uint8_t versionType;

struct initiationPacket {
    versionType vt;
    uint8_t nameLength;
    std::string name;
};

struct dataPacket {
    versionType vt;
    uint32_t agentID;       // low 8bits reserved
    uint64_t timestamp;
    uint16_t dataLength;
    uint16_t metricCount;
    std::vector<uint8_t> data;
    uint32_t checksum;
};

struct serverInitiationPacket {
    versionType vt;
    uint8_t flags;
    uint32_t agentID;       // low 8 bits reserved
    uint32_t responseTime;  // low 16 bits reserved
};

struct serverAckPacket {
    versionType vt;
    uint8_t flags;
};

#endif //CHRONOS_PACKETS_H