include_directories(NetworkProtocol)
include_directories(SystemMetrics)

add_executable(ChronosAgent
        main.cpp
        NetworkProtocol/packets.cpp
        SystemMetrics/systemMetrics.cpp
)

target_link_libraries(ChronosAgent pdh.lib)