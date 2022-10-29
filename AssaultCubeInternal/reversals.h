#pragma once
#include <Windows.h>
#include "Geom.h"

extern int* gameMode;
extern int* numOfPlayers;

class playerent;

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

#define m_teammode    (*gameMode==0 || *gameMode==4 || *gameMode==5 || *gameMode==7 || *gameMode==11 || *gameMode==13 || *gameMode==14 || *gameMode==16 || *gameMode==17 || *gameMode==20 || *gameMode==21)
#define m_botmode     (*gameMode==7 || *gameMode == 8 || *gameMode==12 || (*gameMode>=18 && *gameMode<=21))
#define m_flags       (*gameMode==5 || *gameMode==13 || *gameMode==14 || *gameMode==15)

class weapon
{
public:
	char pad_0x0000[0x4]; //0x0000
	__int32 ID; //0x0004
	playerent* owner; //0x0008
	intptr_t* guninfo; //0x000C
	int* ammo2; //0x0010
	int* ammo; //0x0014
	int* gunWait;
	int shots;
	int breload;
};

class playerent
{
public:
	char _0x0000[4];
	vec vHead; //0x0004
	char _0x0010[36];
	vec vLocation; //0x0034
	vec vViewAngle; //0x0040
	char _0x004C[37];
	BYTE bScoping; //0x0071
	char _0x0072[134];
	__int32 health; //0x00F8
	__int32 armor; //0x00FC
	char _0x0100[292];
	BYTE bAttacking; //0x0224
	char name[16]; //0x0225
	char _0x0235[247];
	BYTE team; //0x032C
	char _0x032D[11];
	BYTE state; //0x0338
	char _0x0339[59];
	weapon* weapon; //0x0374
	char _0x0378[520];
};

class PlayerClass {
public:
	playerent* ent{ nullptr };
	vec vAimbotAngles{ 0,0,0 };	
	float fAngleFromCross{ 0 };

	PlayerClass();
	PlayerClass(intptr_t* player);

	bool IsVisible();
};

struct traceresult_s
{
	vec end{ 0,0,0 };
	bool collided{ false };
};

extern playerent* localPlayer;
