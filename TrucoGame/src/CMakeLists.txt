# CMakeLists.txt in the src directory

cmake_minimum_required(VERSION 3.14)

# C++ version ===========================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Source files
set(SRC_FILES
    # Main
    "TrucoGame.cpp"

    # Controllers
    "controllers/Application.cpp"
    "controllers/TableController.cpp"

    # Models
    "models/client/TcpClient.cpp"
    "models/packets/Packet.cpp"
    "models/server/Player.cpp"
    "models/server/TcpServer.cpp"
    "models/Card.cpp"
    "models/Deck.cpp"
    "models/Table.cpp"
    
    # Views
    "views/trucoGameView/Player/PlayerCards.cpp"
    "views/trucoGameView/Player/PlayerView.cpp"
    "views/trucoGameView/Animator.cpp"
    "views/trucoGameView/CardButton.cpp"
    "views/trucoGameView/CardView.cpp"
    "views/trucoGameView/ScoreView.cpp"
    "views/trucoGameView/TableView.cpp"
    "views/trucoGameView/TrucoGameView.cpp"
    "views/Button.cpp"
    "views/ButtonBase.cpp"
    "views/GraphicManager.cpp"
    "views/MouseState.cpp"
    "views/MutexView.cpp"
    "views/UtilsView.cpp"
 )

# Add source to this project's executable.
add_executable (TrucoGame ${SRC_FILES})

target_link_libraries(TrucoGame 
sfml-graphics 
nlohmann_json
)

install(TARGETS TrucoGame 
ARCHIVE DESTINATION "TrucoGame/lib"
RUNTIME DESTINATION "TrucoGame/lib")
install(DIRECTORY "include"
        DESTINATION "TrucoGame"
)