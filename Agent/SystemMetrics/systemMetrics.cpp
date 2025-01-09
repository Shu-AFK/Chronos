#include "systemMetrics.h"

#include <windows.h>
#include <iphlpapi.h>
#include <iomanip>
#include <pdh.h>

MEMORYSTATUSEX statex;
MIB_IFTABLE *ifTable = nullptr;
DWORD size = 0;

PDH_HQUERY cpuQuery;
PDH_HCOUNTER cpuCounter;

int init(std::string &error) {
    statex.dwLength = sizeof(statex);

    if(GetIfTable(nullptr, &size, false) == ERROR_INSUFFICIENT_BUFFER) {
        ifTable = (MIB_IFTABLE *)malloc(size);
    }

    if(ifTable == nullptr) {
        error = "Unable to get ifTable";
        return -1;
    }

    if(PdhOpenQuery(NULL, 0, &cpuQuery) != ERROR_SUCCESS) {
        error = "Unable to open cpu query";
        return -1;
    }

    if(PdhAddCounter(cpuQuery, TEXT("\\Processor(_Total)\\% Processor Time"), 0, &cpuCounter) != ERROR_SUCCESS) {
        error = "Unable to add cpu counter to query";
        return -1;
    }

    if(PdhCollectQueryData(cpuQuery)) {
        error = "Failed to initialise CPU";
        return -1;
    }

    return 0;
}

void cleanup() {
    if(ifTable != nullptr) {
        free(ifTable);
    }

    if(cpuQuery != nullptr) {
        PdhCloseQuery(cpuQuery);
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

double GetCPULoad() {
    if(PdhCollectQueryData(cpuQuery) != ERROR_SUCCESS) {
        return -1;
    }

    PDH_FMT_COUNTERVALUE counterValue;
    if(PdhGetFormattedCounterValue(cpuCounter, PDH_FMT_DOUBLE, NULL, &counterValue)) {
        return -1;
    }

    return counterValue.doubleValue;
}