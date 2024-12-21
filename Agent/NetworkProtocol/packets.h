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
    uint32_t agentID;
    uint64_t timestamp;
    uint16_t dataLength;
    uint16_t metricCount;
    std::vector<uint8_t> data;
    uint32_t checksum;
};

#endif //CHRONOS_PACKETS_H