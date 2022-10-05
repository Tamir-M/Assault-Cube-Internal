#include "pch.h"
#include "util.h"

void printMenu(bool bHealth, bool bAmmo, bool bRecoil, bool bInstaKill) {
    system("CLS");
    std::string healthState = bHealth ? "x" : " ";
    std::cout << "[" << healthState << ']' << " Health Hack - NUM1" << std::endl;
    std::string ammoState = bAmmo ? "x" : " ";
    std::cout << "[" << ammoState << ']' << " Ammo Hack - NUM2" << std::endl;
    std::string recoilState = bRecoil ? "x" : " ";
    std::cout << "[" << recoilState << ']' << " Recoil Hack - NUM3" << std::endl;
    std::string instaKillState = bInstaKill ? "x" : " ";
    std::cout << "[" << instaKillState << ']' << " Insta Kill- NUM4" << std::endl;
    std::cout << "[ ] Change Kills to 999 - NUM 5" << std::endl;
    std::cout << std::endl << std::endl << "To exit please press END" << std::endl;
}
