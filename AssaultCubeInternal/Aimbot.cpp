#include "pch.h"
#include "Aimbot.h"


std::vector<PlayerClass> playerVector;
std::vector<PlayerClass> targets;

bool playerSorter(PlayerClass& lhs, PlayerClass& rhs) { return lhs.fAngleFromCross < rhs.fAngleFromCross; }

void Aimbot::shoot(void) {
	targets.clear();
	for (PlayerClass p : playerVector) {
		if (p.ent == nullptr || p.ent->state != 0 || m_teammode && p.ent->team == localPlayer->team) continue;
		if (!p.IsVisible()) continue;
		targets.push_back(p);
	}

	for (PlayerClass& p : targets)
	{
		p.vAimbotAngles = CalcAngle(localPlayer->vHead, p.ent->vHead);
		p.fAngleFromCross = GetDistanceVec3(p.vAimbotAngles, localPlayer->vViewAngle);
	}

	sort(targets.begin(), targets.end(), playerSorter);

	if (!targets.empty()) {
		localPlayer->vViewAngle = targets[0].vAimbotAngles;
	}
}

void Aimbot::readPlayerData(void) {
	playerVector.clear();
	int numOfOtherPlayers = *numOfPlayers - 1; // disinclude localPlayer.
	intptr_t* playerArrayAddress = (intptr_t*)0x50F4F8;

	for (int x = 0; x <= numOfOtherPlayers; x++) {
		intptr_t* tempPlayerAddress = (intptr_t*)(*playerArrayAddress + x * 0x4);
		if (*tempPlayerAddress != 0)
			if (*(intptr_t*)*tempPlayerAddress == 0x4E4A98 || *(intptr_t*)*tempPlayerAddress == 0x4E4AC0)
				playerVector.push_back(PlayerClass(tempPlayerAddress));
	}
}