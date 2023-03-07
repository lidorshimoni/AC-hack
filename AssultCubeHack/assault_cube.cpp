#include "assault_cube.h"

AssaultCube::AssaultCube()
{
	// get module
	this->moduleBase = (uintptr_t)GetModuleHandle("ac_client.exe");

	StartShootThread(&this->aimbotSwitch);
}

AssaultCube::~AssaultCube()
{
	if (this->no_fire_delay_hack)
		this->no_fire_delay_hack->~Hack();
	if (this->no_recoil_hack)
		this->no_recoil_hack->~Hack();
}

void AssaultCube::run(bool only_input)
{
	bool should_stop = false;

	// hack loop
	while (!should_stop)
	{
		if (!only_input)
			this->run_once();

		should_stop = !this->handle_user_input();

		Sleep(10);
	}

}


void AssaultCube::run_once()
{
	this->hack_loop_counter++;
	HDC currentHDC = wglGetCurrentDC();

	if (!this->menu || !this->menu->bMenuBuilt)
	{
		this->menu = new Menu_t;
		this->menu->BuildMenu(HackMenu(), viewport[2] * 0.50, viewport[3] * 0.01);
		this->menu->bMenuBuilt = true;
	}
	if (!this->menu->font.bBuilt || currentHDC != this->menu->font.hdc)
	{
		this->menu->font.Build(MENU_FONT_HEIGHT);
	}

	this->read_game_data();

	this->read_player_data();

	this->freeze_hack_values();

	if (this->espSwitch)
	{
		this->draw_esp();
	}

	if (this->menuSwitch)
	{
		menu->Draw();
	}

	if (this->hack_loop_counter % 100 == 0) // every second
	{
		this->print_status();
	}
}

void AssaultCube::draw_esp()
{
	GL::SetupOrtho();
	FW::ESP::ESP(this->players, this->matrix, this->viewport[2], this->viewport[3], this->menu->font);
	GL::RestoreGL();
}

void AssaultCube::read_player_data()
{
	this->player_entity = *(playerent**)(this->moduleBase + PLAYER_ENTITY_PTR_OFFSET);
	this->entity_list_ptr = (playerent * (*)[32])(*(void**)(this->moduleBase + ENTITY_LIST_PTR_OFFSET));
	this->num_of_players = *(int*)(this->moduleBase + NUMBER_OF_PLAYERS_OFFSET);

	if (this->player_entity)
	{
		if (!this->are_hacks_initiallized)
			this->init_hacks();

		this->localPlayer = AC_Player(this->player_entity, this->is_game_in_teams, this->player_entity->team, this->matrix, this->viewport[2], this->viewport[3], this->player_entity);//change this

		this->players.clear();

		for (int i = 1; i < this->num_of_players; i++)
		{
			playerent* e = (*(this->entity_list_ptr))[i];
			if (!e || !e->vTable) continue;

			//std::cout << i << " " << e->name << " - vTable: " << std::hex << e->vTable << std::dec << std::endl;
			players.push_back(AC_Player(e, this->is_game_in_teams, this->player_entity->team, matrix, viewport[2], viewport[3], this->player_entity));
		}

		for (auto& p : players)
		{
			p.Calculate(FW::Aimbot_t::localPlayer);
		}

	}
}

void AssaultCube::read_game_data()
{
	glGetIntegerv(GL_VIEWPORT, this->viewport);

	//if ((*(this->is_game_local) == 0 || *gameMode == 4 || *gameMode == 5 || *gameMode == 7 || *gameMode == 11 || *gameMode == 13 ||
	//	*gameMode == 14 || *gameMode == 16 || *gameMode == 17 || *gameMode == 20 || *gameMode == 21))
	//{
	//	this->is_game_in_teams = true;
	//}
	//else bTeamGame = false;

	//if (*gameMode == 7 || *gameMode == 8 || *gameMode == 12 || (*gameMode >= 18 && *gameMode <= 21))
	//{
	//	bLocalGame = true;
	//}
	//else bLocalGame = false;

}

void AssaultCube::print_status()
{
}

void AssaultCube::freeze_hack_values()
{
	if (this->player_entity)
	{
		if (this->isSuicide)
		{
			this->player_entity->state = DEAD;
			this->isSuicide = false;
		}
		if (this->healthSwitch)
		{
			this->player_entity->health = 1337;
			this->player_entity->armor = 1337;
		}
		if (this->AmmoSwitch)
		{
			this->player_entity->grenade_ammo = 1337;
			this->player_entity->pistol_ammo = 1337;
			this->player_entity->assault_ammo = 1337;
			this->player_entity->carabine_ammo = 1337;
			this->player_entity->double_pistol_ammo = 1337;
			this->player_entity->shotgun_ammo = 1337;
			this->player_entity->smg_ammo = 1337;
			this->player_entity->sniper_ammo = 1337;
		}
		if (this->AmmoSwitch != this->no_recoil_hack->bStatus && this->are_hacks_initiallized )
		{
			this->no_recoil_hack->Toggle();
			this->no_fire_delay_hack->Toggle();
		}
		if (GetAsyncKeyState(VK_RBUTTON) && this->aimbotSwitch)
		{
			GetTarget(FW::Aimbot_t::localPlayer);

			if (target)//good here
			{
				*this->localPlayer.angle = target->angleTo;
				this->bAttack = true;
			}
		}
	}
}

bool AssaultCube::handle_user_input()
{
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		this->healthSwitch = !this->healthSwitch;
	}
	if (GetAsyncKeyState(VK_F2) & 1)
	{
		this->AmmoSwitch = !this->AmmoSwitch;
	}
	if (GetAsyncKeyState(VK_F3) & 1)
	{
		if (this->entity_list_ptr && *(this->entity_list_ptr) && this->player_entity)
		{
			auto dest_position = this->player_entity->feet_pos + (this->player_entity->mouse_xyz.normalized() * 10);
			for (int i = 1; i < sizeof(*(this->entity_list_ptr)) / sizeof(*(entity_list_ptr)[0]) && (*this->entity_list_ptr)[i]; i++)
			{
				if ((*this->entity_list_ptr)[i] && this->player_entity && (*this->entity_list_ptr)[i]->team != this->player_entity->team && (*this->entity_list_ptr)[i] != this->player_entity)
				{
					(*this->entity_list_ptr)[i]->feet_pos = dest_position;
				}
			}
		}
	}
	if (GetAsyncKeyState(VK_F4) & 1)
	{
		if (this->player_entity && this->are_hacks_initiallized)
		{
			this->invisibleSwitch = !this->invisibleSwitch;
			this->invisibility_hack->Toggle();
		}
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		this->aimbotSwitch = !this->aimbotSwitch;
	}
	if (GetAsyncKeyState(VK_F6) & 1)
	{
		this->espSwitch = !this->espSwitch;
	}
	if (GetAsyncKeyState(VK_SPACE) & 1)
	{
		if (this->player_entity)
			this->player_entity->feet_pos.z++;
	}
	if (GetAsyncKeyState(VK_CONTROL) & 1)
	{
		if (this->player_entity)
			this->player_entity->feet_pos.z--;
	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		this->menuSwitch = !this->menuSwitch;
	}
	if (GetAsyncKeyState(VK_F9) & 1)
	{
		this->isSuicide = !this->isSuicide;
	}
	if (GetAsyncKeyState(VK_DELETE) & 1)
	{
		return false;
	}
	return true;
}

void AssaultCube::init_hacks()
{
	this->no_recoil_hack = new Hack((uintptr_t)(this->moduleBase + NO_RECOIL_PATCH_OFFSET), (uint8_t)5);
	this->no_fire_delay_hack = new Hack((uintptr_t)(this->moduleBase + NO_FIRE_DELAY_PATCH_OFFSET), (uint8_t)2);
	this->invisibility_hack = new Hack((uintptr_t)(&(this->player_entity->is_invisible)), "\x01");
	this->are_hacks_initiallized = true;
}

std::vector<row> AssaultCube::HackMenu()
{
	std::vector<row> rows;
	rows.push_back(row(M_HEADER, (char*)"NODER!", nullptr));
	rows.push_back(row(M_FUNCTION, (char*)"[F1] Inf. HP          : ", &this->healthSwitch));
	rows.push_back(row(M_FUNCTION, (char*)"[F2] Inf. Ammo        : ", &this->AmmoSwitch));
	//rows.push_back(row(M_FUNCTION, (char*)"[F2]  Fast Fire        : ", &this->AmmoSwitch));
	rows.push_back(row(M_FUNCTION, (char*)"[F3] Teleport Enemies", nullptr));
	rows.push_back(row(M_FUNCTION, (char*)"[F4] Invisibility     : ", &this->invisibleSwitch));
	rows.push_back(row(M_FUNCTION, (char*)"[F5] Aimbot           : ", &this->aimbotSwitch));
	rows.push_back(row(M_FUNCTION, (char*)"[F6] ESP              : ", &this->espSwitch));
	rows.push_back(row(M_LABEL, (char*)"-----------------------", nullptr));
	rows.push_back(row(M_LABEL, (char*)"[F9] Suicide", &this->isSuicide));
	rows.push_back(row(M_LABEL, (char*)"[INS] Hide Menu", &this->menuSwitch));
	rows.push_back(row(M_LABEL, (char*)"[DELETE] Detach Hack :(", &this->menuSwitch));
	rows.push_back(row(M_FOOTER, (char*)"By Lidor Shimoni", nullptr));
	return rows;
};