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

	Util::Hook::Detour Cmd_ExecFromDisk_Hook;
	bool Cmd_ExecFromDisk(int localClientNum, int controllerIndex, const char* filename)
	{
		Util::Print::Printf("execing %s from disk\n", filename);

		auto Invoke = Cmd_ExecFromDisk_Hook.Invoke<bool(*)(int, int, const char*)>();
		return Invoke(localClientNum, controllerIndex, filename);
	}

	void RegisterHooks()
	{
		Cmd_ExecFromFastFile_Hook.Create(0x822CA408, Cmd_ExecFromFastFile);
		Cmd_ExecFromDisk_Hook.Create(0x822CA390, Cmd_ExecFromDisk);
	}

	void UnregisterHooks()
	{
		Cmd_ExecFromFastFile_Hook.Clear();
		Cmd_ExecFromDisk_Hook.Clear();
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
