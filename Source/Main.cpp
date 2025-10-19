#include "Components\Assets\Assets.h"
#include "Components\Patches.h"
#include "Components\PrintPatches.h"

namespace Loader
{
	typedef struct Module
	{
		const char* name;
		void (*load)();
	} Module;

#define MAX_COMPONENTS 32
	Module g_components[MAX_COMPONENTS];

	int g_componentCount = 0;

	void RegisterModule(const char* name, void (*load)())
	{
		// check for duplicates
		for (int i = 0; i < g_componentCount; ++i)
		{
			if (strcmp(g_components[i].name, name) == 0)
				return; // already registered
		}

		if (g_componentCount < MAX_COMPONENTS)
		{
			g_components[g_componentCount].name = name;
			g_components[g_componentCount].load = load;
			g_componentCount++;
		}
	}

	void LoadModules()
	{
		for (int i = 0; i < g_componentCount; ++i)
		{
			if (g_components[i].load)
				g_components[i].load();
		}

#define REGISTER_MODULE(name) \
    RegisterModule(#name, name::Load);

		REGISTER_MODULE(Assets);
		REGISTER_MODULE(Patches);
		REGISTER_MODULE(PrintPatches);
	}
}

DWORD WINAPI MainThread(LPVOID)
{
	bool loadedModules = false;

	while (!loadedModules)
	{
		DWORD titleId = XamGetCurrentTitleId();
		if (titleId == TITLE_ID)
		{
			Loader::RegisterModule("Patches", Patches::Load);
			Loader::LoadModules(); // Load our modules.
			loadedModules = true;
		}
		Sleep(50);
	}

	return 0;
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
		break;
	}

	return TRUE;
}
