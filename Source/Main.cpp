DWORD WINAPI MainThread(LPVOID)
{
	bool loadedModules = false;

	while (!loadedModules)
	{
		DWORD titleId = XamGetCurrentTitleId();
		if (titleId == TITLE_ID)
		{
			Loader::Load(); // Load our modules.
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
