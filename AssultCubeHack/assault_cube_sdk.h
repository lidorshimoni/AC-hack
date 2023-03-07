#pragma once
#include "stdafx.h"
#include "infra/geometry/geom.h"

#define m_teammode    (*gameMode==0 || *gameMode==4 || *gameMode==5 || *gameMode==7 || *gameMode==11 || *gameMode==13 || *gameMode==14 || *gameMode==16 || *gameMode==17 || *gameMode==20 || *gameMode==21)
#define m_botmode     (*gameMode==7 || *gameMode == 8 || *gameMode==12 || (*gameMode>=18 && *gameMode<=21))
#define m_flags       (*gameMode==5 || *gameMode==13 || *gameMode==14 || *gameMode==15)


enum gameModes
{
	TEAMDEATHMATCH = 0,
	COOPEDIT,
	DEATHMATCH,
	SURVIVOR,
	TEAMSURVIVOR,
	CTF,
	PISTOLFRENZY,
	BOTTEAMDEATHMATCH,
	BOTDEATHMATCH,
	LASTSWISSSTANDING,
	ONESHOTONEKILL,
	TEAMONESHOTONEKILL,
	BOTONESHOTONEKILL,
	HUNTTHEFLAG,
	TEAMKEEPTHEFLAG,
	KEEPTHEFLAG,
	TEAMPF,
	TEAMLSS,
	BOTPISTOLFRENZY,
	BOtlSS,
	BOTTEAMSURVIVOR,
	BOTTEAMONESHOTONEKILL,
	NUM
};

enum mapEntTypes
{
	NOTUSED = 0,
	LIGHT = 1,                      // lightsource, attr1 = radius, attr2 = intensity
	PLAYERSTART = 2,                // attr1 = angle, attr2 = team
	I_CLIPS = 3,
	I_AMMO = 4,
	I_GRENADE = 5,
	I_HEALTH = 6,
	I_HELMET = 7,
	I_ARMOUR = 8,
	I_AKIMBO = 9,
	MAPMODEL = 10,                   // attr1 = angle, attr2 = idx, attr3 = elevation, attr4 = texture
	CARROT = 11,
	LADDER = 12,
	CTF_FLAG = 13,                   // attr1 = angle, attr2 = red/blue
	SOUND = 14,
	CLIP = 15,                       // attr1 = elevation, attr2 = xradius, attr3 = yradius, attr4 = height
	PLCLIP = 16,                     // attr1 = elevation, attr2 = xradius, attr3 = yradius, attr4 = height
	MAXENTTYPES = 17
};

class mapEnt
{
public:
	__int16 x; //0x0000
	__int16 y; //0x0002
	__int16 z; //0x0004
	__int16 attr1; //0x0006
	unsigned char type; //0x0008
	unsigned char attr2; //0x0009
	unsigned char attr3; //0x000A
	unsigned char attr4; //0x000B
	unsigned char bSpawned; //0x000C
	int lastmillis; //0x000D
	unsigned char padding[3];
};//Size=0x0014

class weapon
{
public:
	int mag;
	int ammo;
	int reload_cooldown;
	int shots_fired;
};

class playerent
{
public:
	void *vTable; //0x0000
	Vector3 head_pos; //0x0004
	Vector3 N00000051; //0x0010
	Vector3 force_xyz; //0x001C
	Vector3 feet_pos; //0x0028
	Vector3 mouse_xyz; //0x0034
	float N00000055; //0x0040
	float N00000166; //0x0044
	float N00000167; //0x0048
	float N00000056; //0x004C
	float player_height; //0x0050
	float player_max_height; //0x0054
	char pad_0058[13]; //0x0058
	int8_t is_not_firing; //0x0065
	int8_t is_scoping; //0x0066
	char pad_0067[15]; //0x0067
	int8_t state; //0x0076
	int8_t is_invisible; //0x0077
	char pad_0078[8]; //0x0078
	int8_t is_walking_left; //0x0080
	int8_t is_walking_right; //0x0081
	int8_t is_walking_forward; //0x0082
	int8_t is_walking_backward; //0x0083
	char pad_0084[100]; //0x0084
	void* something_network; //0x00E8
	int32_t health; //0x00EC
	int32_t armor; //0x00F0
	int32_t current_weapon_id; //0x00F4
	int32_t bought_weapon_id; //0x00F8
	int32_t current_weapon_id2; //0x00FC
	char pad_0100[4]; //0x0100
	int32_t knife_mag; //0x0104
	int32_t pistol_mag; //0x0108
	int32_t carabine_mag; //0x010C
	int32_t shotgun_mag; //0x0110
	int32_t smg_mag; //0x0114
	int32_t sniper_mag; //0x0118
	int32_t assualt_mag; //0x011C
	int32_t grenade_mag; //0x0120
	int32_t double_pistol_mag; //0x0124
	int32_t knife_ammo; //0x0128
	int32_t pistol_ammo; //0x012C
	int32_t carabine_ammo; //0x0130
	int32_t shotgun_ammo; //0x0134
	int32_t smg_ammo; //0x0138
	int32_t sniper_ammo; //0x013C
	int32_t assault_ammo; //0x0140
	int32_t grenade_ammo; //0x0144
	int32_t double_pistol_ammo; //0x0148
	int32_t fire_cooldown; //0x014C
	int32_t pistol_reload_cooldown; //0x0150
	int32_t carabine_reload_cooldown; //0x0154
	int32_t shotgun_reload_cooldown; //0x0158
	int32_t smg_reload_cooldown; //0x015C
	int32_t sniper_reload_cooldown; //0x0160
	int32_t assault_reload_cooldown; //0x0164
	int32_t grenade_reload_cooldown; //0x0168
	int32_t double_pistol_reload_cooldown; //0x016C
	int32_t knife_shots_fired; //0x0170
	int32_t pistol_shots_fired; //0x0174
	int32_t carabine_shots_fired; //0x0178
	int32_t shotgun_shots_fired; //0x017C
	int32_t smg_shots_fired; //0x0180
	int32_t sniper_shots_fired; //0x0184
	int32_t assault_shots_fired; //0x0188
	int32_t grenade_shots_fired; //0x018C
	int32_t double_pistol_shots_fired; //0x0190
	char pad_0194[113]; //0x0194
	char name[15]; //0x0205
	char pad_0214[248]; //0x0214
	uint32_t team; //0x030C
	char pad_0310[347]; //0x0310
}; //Size: 0x0468

struct entList
{
	playerent* ents[31];
};

class flagEnt
{
public:
	__int32 team; //0x0000
	mapEnt* mapent; //0x0004
	__int32 number; //0x0008
	playerent* player; //0x000C
	vec3 pos; //0x0010
	__int32 state; //0x001C
	__int32 unknown2; //0x0020
};//Size=0x0024

class flagArray
{
public:
	flagEnt flags[2]; //0x0000
};//Size=0x0048

struct sqr
{
	unsigned char type;
	char floor, ceil;
	unsigned char wtex, ftex, ctex;
	unsigned char r, g, b;
	unsigned char vdelta;
	char defer;
	char occluded;
	unsigned char utex;
	unsigned char tag;
	unsigned char reserved[2];
};

struct traceresult_s
{
	vec3 end;
	bool collided;
};

#define TRACELINE_FUNC_PTR ((void*)0x509010)

#define PLAYER_ENTITY_PTR_OFFSET (0x17E360)
#define ENTITY_LIST_PTR_OFFSET (0x18ac04)
#define NUMBER_OF_PLAYERS_OFFSET (0x18AC0C)
#define VIEW_MATRIX_OFFSET (0x57dfD0)

#define NO_RECOIL_PATCH_OFFSET (0xC2EC3)
#define NO_FIRE_DELAY_PATCH_OFFSET (0xC73EA)
