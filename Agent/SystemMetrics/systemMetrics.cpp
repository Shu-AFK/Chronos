#include "systemMetrics.h"

#include <windows.h>

MEMORYSTATUSEX statex;
static ULARGE_INTEGER lastCPUMeasurement;
static int numProcessors;

void init() {
    statex.dwLength = sizeof(statex);
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