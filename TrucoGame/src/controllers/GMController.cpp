#include "..\..\include\controllers\GMController.h"

namespace TrucoGame {
	namespace Controller {
		int GMController::ModelIdToViewId(int modelId)
		{
			int myId = gameModel->player->playerId;
			return ((modelId + 2) - myId) % 4;
		}
	}
}

