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

#Dear SFML
FetchContent_Declare(
    SFML
    URL ${SPASS_REPO_URL_PREFIX}/SFML/SFML/archive/69ea0cd863aed1d4092b970b676924a716ff718b.zip
)
FetchContent_MakeAvailable(SFML)

# Source code ============================================================================

# Add source to this project's executable.
add_executable (TrucoGame 
    "src/TrucoGame.cpp"  
    
    "src/views/GraphicManager.cpp"
    "src/views/UtilsView.cpp"
    "src/views/trucoGameView/Animator.cpp"
    "src/views/trucoGameView/CardDeck.cpp"
    "src/views/trucoGameView/CardView.cpp"
    "src/views/trucoGameView/PlayerName.cpp"
    "src/views/trucoGameView/TableView.cpp"
    "src/views/trucoGameView/TrucoGameView.cpp"
    "src/views/trucoGameView/ScoreView.cpp"
    "src/controllers/Application.cpp"
    "src/controllers/TableController.cpp"
    
    "src/models/Card.cpp"
    "src/models/Deck.cpp"  

    "include/views/GraphicManager.h"
    "include/views/UtilsView.h"
    "include/views/trucoGameView/Animator.h"
    "include/views/trucoGameView/CardDeck.h"
    "include/views/trucoGameView/CardView.h" 
    "include/views/trucoGameView/PlayerName.h"
    "include/views/trucoGameView/TableView.h"
    "include/views/trucoGameView/TrucoGameView.h"
    "include/views/trucoGameView/ScoreView.h"
    "include/controllers/Application.h"
    "include/controllers/TableController.h"
    
    "include/models/Card.h"
    "include/models/Deck.h" 
    "include/views/trucoGameView/CardsEnum.h"  
 )


target_link_libraries(TrucoGame sfml-graphics)

install(TARGETS TrucoGame 
ARCHIVE DESTINATION "TrucoGame/lib"
RUNTIME DESTINATION "TrucoGame/lib")
install(DIRECTORY "include"
        DESTINATION "TrucoGame"
)
