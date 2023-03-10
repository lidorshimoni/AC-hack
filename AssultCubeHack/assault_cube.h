#pragma once

#include "infra/memory/mem.h"
#include "infra/process/proc.h"
#include "infra/FW.h"
#include "infra/opengl/hack/hackgl.h"
#include "infra/opengl/menu/menu.h"
#include "assault_cube_sdk.h"
#include "AC_Player.h"

class AssaultCube : public FW::Aimbot_t
{
public:
	AssaultCube();
	~AssaultCube();

	void run(); // TODO change this and run_once naming
	void run_once();

	void read_player_data();
	void read_game_data();
	void freeze_hack_values();
	void print_status();
	bool handle_user_input();
	void draw();


	void init_hacks();
	std::vector<row> HackMenu();

private:
	void draw_esp();

	// 
	Menu_t* menu = nullptr;

	// game parameters
	int viewport[4];
	float* matrix = (float*)(VIEW_MATRIX_OFFSET);
	bool is_game_local = true;
	bool is_game_in_teams = true;
	
	/*gameStatus_t gameStatus = GSTAT_GAME;
	sqr* world = (sqr*)0x50A1F8;
	int* sfactor = (int*)0x505BB4;
	int* lastmillis = (int*)0x509EAC;
	int* gameMode = (int*)(0x50F49C);
	int* numOfPlayers = (int*)(0x50f500);*/

	// addresses
	uintptr_t moduleBase;
	playerent* player_entity;
	playerent* (*entity_list_ptr)[32];
	int num_of_players;

	// switches
	bool healthSwitch = false;
	bool AmmoSwitch = false;
	bool invisibleSwitch = false;
	bool aimbotSwitch = false;
	bool espSwitch = false;
	bool menuSwitch = true;
	bool isSuicide = false;
	bool should_stop_and_unload_dll = false;


	int hack_loop_counter = 0;

	// hacks \ patches
	bool are_hacks_initiallized = false;
	Hack* no_recoil_hack;
	Hack* no_fire_delay_hack;
	Hack* invisibility_hack;

};