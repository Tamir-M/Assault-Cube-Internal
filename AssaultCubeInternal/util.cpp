#include "pch.h"
#include "util.h"

void util::printMenu(bool bHealth, bool bAmmo, bool bRecoil, bool bInstaKill, bool bJump, bool bSpeed) {
    system("CLS");
    std::string state = bHealth ? "x" : " ";
    std::cout << "[" << state << ']' << " Health Hack - NUM1" << std::endl;
    state = bAmmo ? "x" : " ";
    std::cout << "[" << state << ']' << " Ammo Hack - NUM2" << std::endl;
    state = bRecoil ? "x" : " ";
    std::cout << "[" << state << ']' << " Recoil Hack - NUM3" << std::endl;
    state = bInstaKill ? "x" : " ";
    std::cout << "[" << state << ']' << " Insta Kill- NUM4" << std::endl;
    std::cout << "[ ] Change Kills to 1337 - NUM 5" << std::endl;
    state = bJump ? "x" : " ";
    std::cout << "[" << state << ']' << " Big Jump - NUM6" << std::endl;
    state = bSpeed ? "x" : " ";
    std::cout << "[" << state << ']' << " Speed Hack - NUM7" << std::endl;
    std::cout << std::endl << std::endl << "To exit please press END" << std::endl;
}
