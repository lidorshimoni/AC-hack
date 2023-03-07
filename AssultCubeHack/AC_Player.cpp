#include "AC_Player.h"

#include "AC_player.h"

//create a AC_Player_t based on reclass ent
//localPlayer
AC_Player::AC_Player(playerent* ent)
{
	pos = &ent->feet_pos;
	head = &ent->head_pos;
	angle = &ent->mouse_xyz;
	//*velocity = ent->velocity; add later
	health = &ent->health;
	if (ent->state == 0)
	{
		state = ALIVE;
	}
	else state = DEAD;
}

AC_Player::AC_Player(playerent* ent, bool bTeamGame, int localTeam, float* matrix, int windowWidth, int windowHeight, playerent* localPlayer)
{
	pos = &ent->feet_pos;
	head = &ent->head_pos;
	angle = &ent->mouse_xyz;
	//*velocity = ent->velocity; add later
	strcpy_s(name, 16, ent->name);
	health = &ent->health;
	team = ent->team;

	//seperate into seperate functions?

	if (bTeamGame == true && ent->team == localTeam)
	{
		bEnemy = false;
	}
	else bEnemy = true;

	if (ent->state == 0)
	{
		state = ALIVE;
	}
	else state = DEAD;

	WorldToScreen(*pos, screen, matrix, windowWidth, windowHeight);

	bVisible = IsVisible(localPlayer);
	//this->bVisible = true;
}


//uint32_t load_eax(uint32_t eax)
//{
//	return eax;
//}

//void _stdcall TraceLine(vec3 from, vec3 to, void * pTracer, bool CheckPlayers, traceresult_s* tr, bool SkipTags);
bool AC_Player::IsVisible(playerent* localent)
{
	//return true;
	auto traceLinePtr = (void(_cdecl *)(vec3, vec3, void*, bool, traceresult_s*, bool))TRACELINE_FUNC_PTR;
	//DWORD traceLineFnc = (DWORD)TRACELINE_FUNC_PTR;
	traceresult_s traceresult;
	traceresult.collided = false;
	vec3 from = localent->head_pos;
	vec3 to = *(this->head);

	//load_eax((uint32_t)&traceresult);
	//traceLinePtr(from, to, localent, true, &traceresult, 0);

	/*__asm
	{
		push 0; bSkipTags
		push 0; bCheckPlayers
		push localent
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [traceresult]
		call traceLinePtr;
		add esp, 36
	}*/

	/*DWORD lpAddr = (DWORD)localent;
	Vec3 to{ this->head->x, this->head->y, this->head->z };

	__asm {
		push 0; bSkipTags
		push 0; bCheckPlayers
		push lpAddr
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [traceresult]
		call traceLineFnc
		add esp, 36
	}*/


	return !traceresult.collided;
}