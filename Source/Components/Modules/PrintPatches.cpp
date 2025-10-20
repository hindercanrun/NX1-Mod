namespace PrintPatches
{
	Util::Hook::Detour Cmd_AddCommand_Hook;
	void Cmd_AddCommand(const char* cmdName, void (__cdecl* function)(), Structs::cmd_function_s* allocedCmd)
	{
		auto existingCmd = Symbols::Cmd_FindCommand(cmdName);
		if (existingCmd)
		{
			Util::Print::Printf("Cmd_AddCommand: %s already defined\n", cmdName);
			return;
		}

		auto Invoke = Cmd_AddCommand_Hook.Invoke<Symbols::Cmd_AddCommand_t>();
		Invoke(cmdName, function, allocedCmd);
	}

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

	bool Dvar_CanChangeValue(const Structs::dvar_t* dvar, Structs::DvarValue value, Structs::DvarSetSource source)
	{
		const char* reason = NULL;

		if ((dvar->flags & 0x2000) != 0)
		{
			reason = Util::String::Va("%s is read only.\n", dvar->name);
		}
		else if ((dvar->flags & 0x800) != 0)
		{
			reason = Util::String::Va("%s is write protected.\n", dvar->name);
		}
		else if (source == Structs::DVAR_SOURCE_EXTERNAL && Symbols::Dvar_IsCheatProtected(dvar->flags))
		{
			reason = Util::String::Va("%s is cheat protected.\n", dvar->name);
		}

		Util::Print::Printf(reason);
		return false;
	}

	Util::Hook::Detour Dvar_SetVariant_Hook;
	void Dvar_SetVariant(Structs::dvar_t* dvar, Structs::DvarValue value, Structs::DvarSetSource source)
	{
		if (dvar && dvar->name && *dvar->name)
		{
			//Util::Print::Printf("    dvar set %s %s\n", dvar->name, Symbols::Dvar_ValueToString(dvar, value));
		}

		auto Invoke = Dvar_SetVariant_Hook.Invoke<bool(*)(Structs::dvar_t*, Structs::DvarValue, Structs::DvarSetSource)>();
		Invoke(dvar, value, source);
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

	void Hooks()
	{
		Cmd_AddCommand_Hook.Create(0x822C96F8, Cmd_AddCommand);
		Cmd_ExecFromFastFile_Hook.Create(0x822CA408, Cmd_ExecFromFastFile);
		Cmd_ExecFromDisk_Hook.Create(0x822CA390, Cmd_ExecFromDisk);

		Dvar_SetVariant_Hook.Create(0x82374380, Dvar_SetVariant);

		MSG_InitHuffman_Hook.Create(0x822E7AB0, MSG_InitHuffman);
	}

	void ClearHooks()
	{
		Cmd_AddCommand_Hook.Clear();
		Cmd_ExecFromFastFile_Hook.Clear();
		Cmd_ExecFromDisk_Hook.Clear();

		Dvar_SetVariant_Hook.Clear();

		MSG_InitHuffman_Hook.Clear();
	}

	void Load()
	{
		Hooks();
	}

	void Unload()
	{
		ClearHooks();
	}
}
