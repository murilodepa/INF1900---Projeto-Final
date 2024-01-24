# CMakeLists.txt in the src directory

# Source files
set(SRC_FILES
    # Main
    "TrucoGame.cpp"

    # Controllers
    "controllers/Application.cpp"
    "controllers/TableController.cpp"

    # Models
    "models/Card.cpp"
    "models/Deck.cpp"
    
    # Views
    "views/trucoGameView/Player/PlayerCards.cpp"
    "views/trucoGameView/Player/PlayerView.cpp"
    "views/trucoGameView/Animator.cpp"
    "views/trucoGameView/CardView.cpp"
    "views/trucoGameView/ScoreView.cpp"
    "views/trucoGameView/TableView.cpp"
    "views/trucoGameView/TrucoGameView.cpp"
    "views/Button.cpp"
    "views/GraphicManager.cpp"
    "views/MainMenuState.cpp"
    "views/State.cpp"
    "views/UtilsView.cpp"
)

# Add source to this project's executable.
add_executable (TrucoGame ${SRC_FILES})

target_link_libraries(TrucoGame sfml-graphics)

install(TARGETS TrucoGame 
ARCHIVE DESTINATION "TrucoGame/lib"
RUNTIME DESTINATION "TrucoGame/lib")
install(DIRECTORY "include"
        DESTINATION "TrucoGame"
)