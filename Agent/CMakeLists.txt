include_directories(NetworkProtocol)

add_executable(ChronosAgent
        main.cpp
        NetworkProtocol/packets.cpp
)