#pragma once
#include <Windows.h>
#include <thread>
#include "opengl/menu/menu.h"
#include "aimbot/aimbot.h"
#include "esp/esp.h"

enum gameStatus_t
{
	GSTAT_LOBBY, GSTAT_GAME
};

namespace FW
{
	class Game
	{
	public:
		int windowWidth, windowHeight;
		//what else?
	};
};