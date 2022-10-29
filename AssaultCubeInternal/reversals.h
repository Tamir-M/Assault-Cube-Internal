#pragma once
#include <Windows.h>

struct vec { float x, y, z; };

extern int* gameMode;
extern int* numOfPlayers;

class playerent;

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

extern playerent* localPlayer;
