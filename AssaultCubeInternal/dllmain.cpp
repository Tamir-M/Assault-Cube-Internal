// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include "mem.h"
#include "proc.h"
#include "util.h"

DWORD jmpBackAddy;
void __declspec(naked) InstaKill() {
    __asm {
        mov [ebx + 04], 0
        mov eax, edi
        jmp [jmpBackAddy]
    }
}

DWORD WINAPI HackThread(HMODULE hModule) {
    // Create Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Starting the cheat." << std::endl;  

    // Get Module Base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    bool bHealth = false, bAmmo = false, bRecoil = false, bInstaKill = false;

    // Print the menu:
    util::printMenu(bHealth, bAmmo, bRecoil, bInstaKill);

    // Hack Loop
    uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10f4f4);
    while (true) {
        //Key Inputs
        if (GetAsyncKeyState(VK_END) & 1) {
            mem::Patch((BYTE*)(moduleBase + 0x29D1F), (BYTE*)"\x29\x7b\x04\x8b\xc7", 5);
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bHealth = !bHealth;
            util::printMenu(bHealth, bAmmo, bRecoil, bInstaKill);
        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            bAmmo = !bAmmo;
            util::printMenu(bHealth, bAmmo, bRecoil, bInstaKill);
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            bRecoil = !bRecoil;
            util::printMenu(bHealth, bAmmo, bRecoil, bInstaKill);

            if (bRecoil) mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
            else mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10);
        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
            bInstaKill = !bInstaKill;
            util::printMenu(bHealth, bAmmo, bRecoil, bInstaKill);

            int hookLength = 5;
            DWORD hookAddress = (moduleBase + 0x29D1F);
            jmpBackAddy = hookAddress + hookLength;

            if (bInstaKill) mem::Hook((void*)hookAddress, InstaKill, hookLength);
            else mem::Patch((BYTE*)(hookAddress), (BYTE*)"\x29\x7b\x04\x8b\xc7", hookLength);
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
            *(int*)(*localPlayerPtr + 0x1FC) = 1337;
        }

        // Continues Write/Freeze

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

