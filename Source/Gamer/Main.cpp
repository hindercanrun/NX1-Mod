#include "Std_Include.h"

#include "Loader/ModulesLoader.h"

DWORD WINAPI MainThread(LPVOID)
{
	while (true)
	{
		DWORD titleId = XamGetCurrentTitleId();
		if (titleId == TITLE_ID)
		{
			ModulesLoader::Load(); // Load our modules.
		}
	}

	return FALSE;
}

BOOL APIENTRY DllMain(
	HANDLE handle,
	DWORD reason,
	LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE hThread = CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
		if (hThread)
		{
			CloseHandle(hThread);
		}
		break;
	}
	case DLL_PROCESS_DETACH:
		// This case is useless on Xenia because it doesn't have a dashboard system.
		// So, code here will only run on Xbox. ... I don't even support Xbox so this case is actually useless lol
		ModulesLoader::Unload(); // Remove our hooks.
		break;
	}

	return TRUE;
}
