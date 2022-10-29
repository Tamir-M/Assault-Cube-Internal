#include "pch.h"
#include "reversals.h"


int* gameMode = (int*)(0x50F49C);
int* numOfPlayers = (int*)(0x50F500);
playerent* localPlayer = *(playerent**)(0x50F4F4);