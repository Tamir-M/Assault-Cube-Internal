#include "pch.h"
#include "util.h"

bool bHealth = false;
bool bAmmo = false;
bool bRecoil = false;
bool bInstaKill = false;
bool bJump = false;
bool bSpeed = false;
bool bAimbot = false;

void util::printMenu() {
    system("CLS");
    std::string state = bHealth ? "x" : " ";
    std::cout << "[" << state << ']' << " Health Hack - NUM1" << std::endl;

    state = bAmmo ? "x" : " ";
    std::cout << "[" << state << ']' << " Ammo Hack - NUM2" << std::endl;

    state = bRecoil ? "x" : " ";
    std::cout << "[" << state << ']' << " Recoil Hack - NUM3" << std::endl;
    
    state = bInstaKill ? "x" : " ";
    std::cout << "[" << state << ']' << " Insta Kill- NUM4" << std::endl;
    
    state = bJump ? "x" : " ";
    std::cout << "[" << state << ']' << " Big Jump - NUM5" << std::endl;
    
    state = bSpeed ? "x" : " ";
    std::cout << "[" << state << ']' << " Speed Hack - NUM6" << std::endl;

    state = bAimbot ? "x" : " ";
    std::cout << "[" << state << "]" << " Aimbot - NUM7" << std::endl;
    
    std::cout << std::endl << std::endl << "To exit please press END" << std::endl;
}
