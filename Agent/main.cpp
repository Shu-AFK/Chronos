#include "packets.h"
#include "packetConstants.h"
#include "systemMetrics.h"

#include <iostream>

int main() {
    std::string errorStr;
    if(init(errorStr) != 0) {
        std::cout << "Can't init system metrics: " << errorStr << std::endl;
    }



    cleanup();
    return 0;
}