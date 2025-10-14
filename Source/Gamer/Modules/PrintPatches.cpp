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

	Util::Hook::Detour MSG_InitHuffman_Hook;
	void MSG_InitHuffman()
	{
		int start = Symbols::Sys_Milliseconds();

		auto Invoke = MSG_InitHuffman_Hook.Invoke<void(*)()>();
		Invoke();

		int end = Symbols::Sys_Milliseconds();

		Util::Print::Printf("Huffman Took %d Milliseconds\n", end - start);
	}

	void RegisterHooks()
	{
		Cmd_ExecFromFastFile_Hook.Create(0x822CA408, Cmd_ExecFromFastFile);
		Cmd_ExecFromDisk_Hook.Create(0x822CA390, Cmd_ExecFromDisk);

		MSG_InitHuffman_Hook.Create(0x822E7AB0, MSG_InitHuffman);
	}

	void UnregisterHooks()
	{
		Cmd_ExecFromFastFile_Hook.Clear();
		Cmd_ExecFromDisk_Hook.Clear();

		MSG_InitHuffman_Hook.Clear();
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
