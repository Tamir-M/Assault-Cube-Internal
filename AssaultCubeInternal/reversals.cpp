#include "pch.h"
#include "reversals.h"


int* gameMode = (int*)(0x50F49C);
int* numOfPlayers = (int*)(0x50F500);
playerent* localPlayer = *(playerent**)(0x50F4F4);

PlayerClass::PlayerClass(intptr_t* player) {
	ent = (playerent*)*(intptr_t*)player;
}

bool PlayerClass::IsVisible() {
	intptr_t traceLine = 0x048a310;
	traceresult_s traceresult;
	traceresult.collided = false;
	vec from = localPlayer->vHead;
	vec to = ent->vHead;

	__asm
	{
		push 0; bSkipTags
		push 0; bCheckPlayers
		push localPlayer
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [traceresult]
		call traceLine;
		add esp, 36
	}
	return !traceresult.collided;
}