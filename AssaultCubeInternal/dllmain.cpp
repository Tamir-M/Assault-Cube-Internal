// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include "mem.h"
#include "proc.h"
#include "util.h"
#include "reversals.h"
#include "Aimbot.h"


typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);
twglSwapBuffers owglSwapBuffers;


DWORD jmpBackAddy;
void __declspec(naked) InstaKill() {
    __asm {
        mov[ebx + 04], 0
        mov eax, edi
        jmp[jmpBackAddy]
    }
}


BOOL __stdcall hkwglSwapBuffers(HDC hDc) {
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
        bHealth = !bHealth;
        util::printMenu();
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
        bAmmo = !bAmmo;
        util::printMenu();
    }
    if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
        bRecoil = !bRecoil;
        util::printMenu();

        if (bRecoil) mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
        else mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10);
    }
    if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
        bInstaKill = !bInstaKill;
        util::printMenu();

        int hookLength = 5;
        DWORD hookAddress = (moduleBase + 0x29D1F);
        jmpBackAddy = hookAddress + hookLength;

        if (bInstaKill) mem::Hook((void*)hookAddress, InstaKill, hookLength);
        else mem::Patch((BYTE*)(hookAddress), (BYTE*)"\x29\x7b\x04\x8b\xc7", hookLength);
    }
    if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
        bJump = !bJump;
        util::printMenu();
        if (bJump) mem::Patch((BYTE*)(moduleBase + 0x5B318), (BYTE*)"\xd9\x05\x44\xE2\x4e\x00", 6);
        else mem::Patch((BYTE*)(moduleBase + 0x5B318), (BYTE*)"\xd9\x05\x4c\xe2\x4e\x00", 6);
    }
    if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
        bSpeed = !bSpeed;
        util::printMenu();
        if (bSpeed) {
            mem::Patch((BYTE*)(moduleBase + 0x5BEA0), (BYTE*)"\xb8\x03\x00\x00\x00", 5);
            mem::Patch((BYTE*)(moduleBase + 0x5BE40), (BYTE*)"\xb8\xfd\xff\xff\xff", 5);
            mem::Patch((BYTE*)(moduleBase + 0x5BF00), (BYTE*)"\xb8\x03\x00\x00\00", 5);
            mem::Patch((BYTE*)(moduleBase + 0x5BF60), (BYTE*)"\xb8\xfd\xff\xff\xff", 5);
        }
        else {
            mem::Patch((BYTE*)(moduleBase + 0x5BEA0), (BYTE*)"\xb8\x01\x00\x00\x00", 5);
            mem::Patch((BYTE*)(moduleBase + 0x5BE40), (BYTE*)"\xb8\xff\xff\xff\xff", 5);
            mem::Patch((BYTE*)(moduleBase + 0x5BF00), (BYTE*)"\xb8\x01\x00\x00\00", 5);
            mem::Patch((BYTE*)(moduleBase + 0x5BF60), (BYTE*)"\xb8\xff\xff\xff\xff", 5);
        }
    }
    if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
        bAimbot = !bAimbot;
        if (bAimbot) Aimbot::readPlayerData();
        util::printMenu();
    }
    // Continues Write/Freeze

    if (localPlayer) {
        if (bHealth) localPlayer->health = 1337;
        if (bAmmo) *(localPlayer->weapon->ammo) = 1337;
        if (bAimbot && (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0) {
            Aimbot::shoot();
        }
    }

    return owglSwapBuffers(hDc);
}

DWORD WINAPI HackThread(HMODULE hModule) {
    // Create Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Starting the cheat." << std::endl;  

    // Get Module Base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

    // Print the menu:
    util::printMenu();

    Aimbot::readPlayerData();



    owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
    owglSwapBuffers = (twglSwapBuffers)mem::TrampHook32((BYTE*)owglSwapBuffers, (BYTE*)hkwglSwapBuffers, 5);


    //Disabling all features incase they were on when turning off the hack:
    /*mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10);
    mem::Patch((BYTE*)(moduleBase + 0x29D1F), (BYTE*)"\x29\x7b\x04\x8b\xc7", 5);
    mem::Patch((BYTE*)(moduleBase + 0x5B318), (BYTE*)"\xd9\x05\x4c\xe2\x4e\x00", 6);
    mem::Patch((BYTE*)(moduleBase + 0x5BEA0), (BYTE*)"\xb8\x01\x00\x00\x00", 5);
    mem::Patch((BYTE*)(moduleBase + 0x5BE40), (BYTE*)"\xb8\xff\xff\xff\xff", 5);
    mem::Patch((BYTE*)(moduleBase + 0x5BF00), (BYTE*)"\xb8\x01\x00\x00\00", 5);
    mem::Patch((BYTE*)(moduleBase + 0x5BF60), (BYTE*)"\xb8\xff\xff\xff\xff", 5);*/


    //Cleanup & Eject.
    //fclose(f);
    //FreeConsole();
    //FreeLibraryAndExitThread(hModule, 0);
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

