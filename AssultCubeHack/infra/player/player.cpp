#include "player.h"

//base functions to be overridden by inherited class

bool FW::Player_t::IsValid()
{
	return (health > 0 && this->state == ALIVE);
}

void FW::Player_t::Calculate(Player_t localPlayer)
{
	this->dist = Distance(*localPlayer.pos, *(this->pos));
	this->angleTo = CalcAngle(*localPlayer.pos, *(this->pos));
	this->angleDiff = Distance(*localPlayer.angle, this->angleTo);
}

bool FW::Player_t::IsVisible(Player_t localPlayer)
{
	//stub for overridden function
	return !screen.iszero();
}