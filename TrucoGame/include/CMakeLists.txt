# CMakeLists.txt in the include directory

cmake_minimum_required(VERSION 3.14)

# C++ version ===========================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header files
set(HEADER_FILES
    # Controllers
    "controllers/Application.h"
    "controllers/TableController.h"

    # Models
    "models/client/TcpClient.h"
    "models/client/ClientGameManager.h"
    "models/packets/CardPacket.h"
    "models/packets/EndRoundPacket.h"
    "models/packets/EndTurnPacket.h"
    "models/packets/Packet.h"
    "models/packets/PlayerPlayPacket.h"
    "models/packets/StartGamePacket.h"
    "models/packets/StartRoundPacket.h"
    "models/packets/TrucoPacket.h"
    "models/packets/ElevenHandPacket.h"
    "models/packets/ElevenHandResponsePacket.h"
    "models/server/AIPlayer.h"
    "models/server/TcpClientPlayer.h"
    "models/server/TcpServer.h"
    "models/server/ServerGameManager.h" 
    "models/Card.h"
    "models/Deck.h"
    "models/ErrorCode.h"
    "models/Player.h"
    "models/Score.h"
    "models/Table.h"

    # Views
    "views/button/ButtonBase.h"
    "views/mouse/MouseState.h"
    "views/text/TextView.h"

    "views/trucoGameView/buttonsTruco/AcceptTrucoButton.h"
    "views/trucoGameView/buttonsTruco/CardButton.h"
    "views/trucoGameView/buttonsTruco/IncreaseStakesButton.h"
    "views/trucoGameView/buttonsTruco/RefuseTrucoButton.h"
    "views/trucoGameView/buttonsTruco/TrucoButton.h"
    "views/trucoGameView/player/PlayerCards.h"
    "views/trucoGameView/player/PlayerView.h"
    "views/trucoGameView/Animator.h"
    "views/trucoGameView/CardDeck.h"
    "views/trucoGameView/CardView.h"
    "views/trucoGameView/PopUpTruco.h"
    "views/trucoGameView/ScoreView.h"
    "views/trucoGameView/TableView.h"
    "views/trucoGameView/TrucoGameView.h"
    "views/GraphicManager.h"
    "views/utils/CardsEnum.h"
    "views/utils/MutexView.h"
    "views/utils/StakesValueEnum.h"
    "views/utils/UtilsView.h"
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Headers-only library
add_library(TrucoGameHeaders INTERFACE)
target_sources(TrucoGameHeaders INTERFACE ${HEADER_FILES})
