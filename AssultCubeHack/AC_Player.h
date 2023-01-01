#pragma once
#include "infra/player/player.h"
#include "assault_cube_sdk.h"

class AC_Player : public FW::Player_t
{
public:
	AC_Player(playerent* ent); //local
	AC_Player(playerent* ent, bool bTeamGame, int localTeam, float* matrix, int windowWidth, int windowHeight, playerent* localPlayer);

	virtual bool IsVisible(playerent* localPlayer);
	bool IsValid();
};

