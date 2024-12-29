#include "systemMetrics.h"

#include <windows.h>
#include <iphlpapi.h>
#include <iomanip>

MEMORYSTATUSEX statex;
MIB_IFTABLE *ifTable = nullptr;
DWORD size = 0;

int init() {
    statex.dwLength = sizeof(statex);

    if(GetIfTable(nullptr, &size, false) == ERROR_INSUFFICIENT_BUFFER) {
        ifTable = (MIB_IFTABLE *)malloc(size);
    }

    if(ifTable == nullptr) {
        return -1;
    }

    return 0;
}

void cleanup() {
    if(ifTable != nullptr) {
        free(ifTable);
    }
}

bool updateMemoryStruct() {
    return GlobalMemoryStatusEx(&statex);
}

int getMemoryPercent() {
    return static_cast<int>(statex.dwMemoryLoad);
}

float getTotalMemory() {
    return BYTESTOGB(statex.ullTotalPhys);
}

float getAvailMemory() {
    return BYTESTOGB(statex.ullAvailPhys);
}