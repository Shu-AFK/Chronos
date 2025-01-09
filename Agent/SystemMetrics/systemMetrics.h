#ifndef CHRONOS_SYSTEMMETRICS_H
#define CHRONOS_SYSTEMMETRICS_H

#define GB 1073741824.0f
#define BYTESTOGB(X) (X/GB)

#include <string>

int init(std::string &error);
void cleanup();

bool updateMemoryStruct();
int getMemoryPercent();
float getTotalMemory();
float getAvailMemory();

double GetCPULoad();

#endif //CHRONOS_SYSTEMMETRICS_H
