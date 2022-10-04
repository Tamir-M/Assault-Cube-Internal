// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include "mem.h"
#include "proc.h"

void printMenu(bool bHealth, bool bAmmo, bool bRecoil) {
    system("CLS");
    std::string healthState = bHealth ? "x" : " ";
    std::cout << "[" << healthState << ']' << " Health Hack - NUM1" << std::endl;
    std::string ammoState = bAmmo ? "x" : " ";
    std::cout << "[" << ammoState << ']' << " Ammo Hack - NUM2" << std::endl;
    std::string recoilState = bRecoil ? "x" : " ";
    std::cout << "[" << recoilState << ']' << " Recoil Hack - NUM3" << std::endl;
    std::cout << std::endl << std::endl << "To exit please press END" << std::endl;
}

DWORD WINAPI HackThread(HMODULE hModule) {
    // Create Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Started from the bottom now we here." << std::endl;  

    // Get Module Base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    bool bHealth = false, bAmmo = false, bRecoil = false;

    // Print the menu:
    printMenu(false, false, false);

    // Hack Loop
    while (true) {
        //Key Inputs
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth = !bHealth;
            printMenu(bHealth, bAmmo, bRecoil);
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bAmmo = !bAmmo;
            printMenu(bHealth, bAmmo, bRecoil);
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bRecoil = !bRecoil;
            printMenu(bHealth, bAmmo, bRecoil);

            if (bRecoil) {
                mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
            }else {
                mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10);
            }
        }
        // Continues Write/Freeze
        uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10f4f4);

        if (localPlayerPtr) {
            if (bHealth) *(int*)(*localPlayerPtr + 0xf8) = 1337;
            if (bAmmo) *(int*)mem::FindDMAAddy(moduleBase + 0x10f4f4, { 0x374, 0x14, 0x0 }) = 1337;
        }
    }


    //Cleanup & Eject.
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

