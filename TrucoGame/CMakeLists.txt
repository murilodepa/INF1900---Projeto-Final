# CMakeList.txt : CMake project for TrucoGame, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.14)

project(TrucoGame)

include(FetchContent)

# C++ version ===========================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# External libs =========================================================================

set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

#Dear ImGui
FetchContent_Declare(
    SFML
    URL ${SPASS_REPO_URL_PREFIX}/SFML/SFML/archive/69ea0cd863aed1d4092b970b676924a716ff718b.zip
)
FetchContent_MakeAvailable(SFML)

#JSON for modern C++
FetchContent_Declare(
        nlohmann
        GIT_REPOSITORY  "https://github.com/onavratil-monetplus/json"
        GIT_TAG         "master"
)
FetchContent_MakeAvailable(nlohmann)

# Source code ============================================================================

# Add source to this project's executable.
add_executable (TrucoGame 
    "src/TrucoGame.cpp"  
    
    "src/views/Camera.cpp"
    "src/views/GraphicManager.cpp"
    "src/controllers/Application.cpp"
    "src/models/server/Client.cpp"
    "src/models/server/TcpServer.cpp"
    "src/models/Packet.cpp"

    "include/views/Camera.h"
    "include/views/GraphicManager.h"
    "include/controllers/Application.h"
    "include/models/ErrorCode.h"
    "include/models/Packet.h"
    "include/models/server/TcpServer.h"
    "include/models/server/Client.h"
)

target_link_libraries(TrucoGame sfml-graphics)
target_link_libraries(TrucoGame nlohmann_json::nlohmann_json)

install(TARGETS TrucoGame 
ARCHIVE DESTINATION "TrucoGame/lib"
RUNTIME DESTINATION "TrucoGame/lib")
install(DIRECTORY "include"
        DESTINATION "TrucoGame"
)
