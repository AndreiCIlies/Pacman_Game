#pragma once

#include "typedefs.h"


namespace pac
{
	struct GameplaySettings
	{
		TickType mTicksPerSecond = 3;
		TickType mPacmanTicksPerMove = 2;
		TickType mGhostTicksPerMove = 2;
		TickType mGhostScaredTicksPerMove = 3;
		TickType mPowerUpDuration = 100;
		ScoreType mScorePerCoin = 100;
		ScoreType mScorePerPowerUp = 500;
		ScoreType mScorePerGhost = 1000;
		uint8_t ghostCount = 1;
		TickType mGhostInitialSpawnDelay = 15;
		TickType mGhostRespawnDelay = 100;
	};
}
