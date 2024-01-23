# CMakeLists.txt in the include directory

# Header files
set(HEADER_FILES
    "controllers/Application.h"
    "controllers/TableController.h"

    "models/Card.h"
    "models/Deck.h"

    "views/trucoGameView/Animator.h"
    "views/trucoGameView/CardDeck.h"
    "views/trucoGameView/CardsEnum.h"
    "views/trucoGameView/CardView.h"
    "views/trucoGameView/PlayerName.h"
    "views/trucoGameView/PlayerView.h"
    "views/trucoGameView/ScoreView.h"
    "views/trucoGameView/TableView.h"
    "views/trucoGameView/TrucoGameView.h"

    "views/Button.h"
    "views/GraphicManager.h"
    "views/MainMenuState.h"
    "views/State.h"
    "views/UtilsView.h"
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Headers-only library
add_library(TrucoGameHeaders INTERFACE)
target_sources(TrucoGameHeaders INTERFACE ${HEADER_FILES})
