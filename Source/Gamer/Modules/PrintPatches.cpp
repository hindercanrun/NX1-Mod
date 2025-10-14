#include "..\Std_Include.h"
#include "PrintPatches.h"

namespace PrintPatches
{
	Util::Hook::Detour Cmd_ExecFromFastFile_Hook;
	bool Cmd_ExecFromFastFile(int localClientNum, int controllerIndex, const char* filename)
	{
		Util::Print::Printf("execing %s from fastfile\n", filename);

		auto Invoke = Cmd_ExecFromFastFile_Hook.Invoke<bool(*)(int, int, const char*)>();
		return Invoke(localClientNum, controllerIndex, filename);
	}

	void RegisterHooks()
	{
		Cmd_ExecFromFastFile_Hook.Create(0x822CA408, Cmd_ExecFromFastFile);
	}

	void UnregisterHooks()
	{
		Cmd_ExecFromFastFile_Hook.Clear();
	}

	void Load()
	{
		RegisterHooks();
	}

	void Unload()
	{
		UnregisterHooks();
	}
}
