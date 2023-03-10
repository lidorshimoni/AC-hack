// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "assault_cube.h"

AssaultCube* AC;
bool can_safely_unhook = true;

//wglSwapBuffers Hook
GL::twglSwapBuffers owglSwapBuffers;
BOOL __stdcall hwglSwapBuffers(HDC hDc)
{
	static int recursive_count = 0;
	recursive_count++;
	can_safely_unhook = false;
	AC->draw();

	can_safely_unhook = true;
	recursive_count--;
	return owglSwapBuffers(hDc);
}

DWORD WINAPI HackThread(HMODULE hModule) {
	// create console
	//AllocConsole();
	//FILE* stdout_file;
	//freopen_s(&stdout_file, "CONOUT$", "w", stdout);


	AC = new AssaultCube();
	GL::Hook("wglSwapBuffers", (uintptr_t&)owglSwapBuffers, &hwglSwapBuffers);
	AC->run();
	while (!can_safely_unhook )
	{
		Sleep(5);
	}
	
	//Sleep(10000);


	GL::unHook("wglSwapBuffers", (void*)owglSwapBuffers);
	AC->~AssaultCube();
	//fclose(stdout_file);
	//FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

// Problems to fix
// 1. cant unload hack always. dependent on shooting thread
// 2. aimbot wont work - the traceline function is causing artifacts...
// 3. teleport enemies -> because mouse x,y is not a vector...need to convert mouse x,y to orientation
// 
// todo Features:
// 1. show points on map
// 2. teleport
// 3. 1 hit kill
// 4. disable knockback
// 5. teleport to flags

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		std::cout << "PROCESS ATTACH" << std::endl;
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
		break;
	}
	case DLL_THREAD_ATTACH:
		std::cout << "THREAD ATTACH" << std::endl;
		break;
	case DLL_THREAD_DETACH:
		std::cout << "THREAD DEATACH" << std::endl;
		break;
	case DLL_PROCESS_DETACH:
		std::cout << "PROCESS DEATACH" << std::endl;
		break;
	}
	return TRUE;
}