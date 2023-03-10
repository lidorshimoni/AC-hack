#pragma once
#include "../../stdafx.h"
#include "../geometry/geom.h"
#include "../player/player.h"

namespace FW
{
	class Aimbot_t
	{
	public:
		bool bTargetLock = false;
		bool bAttack = false;
		vec3 crossHair;

		Player_t localPlayer;
		std::vector<Player_t> players;
		std::vector<Player_t*> targets;
		Player_t* target = nullptr;
		std::thread * shootThread = nullptr;

		void StartShootThread(bool* bAimbot, bool* should_stop);
		void GetCrossHair(int viewport[4]);
		void MoveMouse(vec3 point, int windowWidth, int windowHeight);
		void GetTarget(Player_t localPlayer);
	};

	void ShootThread(Aimbot_t* aimbot, bool* bAimbot, bool* should_stop);
	bool SortByAngle(Player_t* lhs, Player_t* rhs);
}