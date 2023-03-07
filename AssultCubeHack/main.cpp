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
	AC->run_once();

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
	AC->run(true);

	while (!can_safely_unhook )
	{
		Sleep(5);
	}
	GL::unHook("wglSwapBuffers", (void*)owglSwapBuffers);
	AC->~AssaultCube();

	//fclose(stdout_file);
	//FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}