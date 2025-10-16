namespace Patches
{
	// This function gets called once by the game, so it's okay to do our printing in.
	Util::Hook::Detour FS_InitFilesystem_Hook;
	void FS_InitFilesystem()
	{
		DWORD start = GetTickCount();

		// Print our loaded modules.
		Util::Print::Printf("\nLoading modules...\n");
		for (int i = 0; i < ModulesLoader::g_moduleCount; ++i)
		{
			Util::Print::Printf("%d: %s\n", i + 1, ModulesLoader::g_modules[i].name);
		}
		
		// Print the time it took to load them all.
		DWORD end = GetTickCount();
		DWORD duration = end - start;
		Util::Print::Printf("Loaded all modules in %lu ms\n\n", duration);

		auto Invoke = FS_InitFilesystem_Hook.Invoke<void(*)()>();
		Invoke();
	}

	void PlayIntroMovies()
	{
		Symbols::Cbuf_AddText(0, "autocinematic title\n");
	}

	Util::Hook::Detour Com_Init_Try_Block_Function_Hook;
	void Com_Init_Try_Block_Function(const char* p_command_line)
	{
		auto Invoke = Com_Init_Try_Block_Function_Hook.Invoke<void(*)(const char*)>();
		Invoke(p_command_line);

		PlayIntroMovies();
	}

	Util::Hook::Detour DB_InflateInit_Hook;
	void DB_InflateInit(int fileIsSecure)
	{
		Symbols::DB_AuthLoad_InflateInit(&Symbols::g_load->stream, fileIsSecure, Symbols::g_load->p_file->name);
	}

	Util::Hook::Detour getBuildNumber_Hook;
	const char* getBuildNumber()
	{
		return Util::String::Va("1 01/05/2012 11:39:15 NX1GAMING");
	}

	void Cmd_LoadZone_f()
	{
		Structs::XZoneInfo zoneInfo;

		zoneInfo.allocFlags = 1;
		zoneInfo.name = "ui";
		zoneInfo.freeFlags = 0;

		Symbols::DB_LoadXAssets(&zoneInfo, 1, 1);
	}

	void AddCommands()
	{
		Util::Command::Add("loadzone", Cmd_LoadZone_f);
	}

	Util::Hook::Detour Cmd_Init_Hook;
	void Cmd_Init()
	{
		auto Invoke = Cmd_Init_Hook.Invoke<void(*)()>();
		Invoke();

		AddCommands();
	}

	void StringEdits()
	{
		// example:
		// Util::Hook::SetString(<address>, <string>); // <comment> (optional)

		Util::Hook::SetString(0x820195B4, "NX1 GAMING "); // NX1 GAMEING !!!!!!
		Util::Hook::SetString(0x8201953C, "Build 1866586"); // shorten that string!
	}

	void DVarEdits()
	{
		// example:
		// Util::Hook::SetValue(<address>, <value>); // <comment> (optional)

		Util::Hook::SetValue(0x824D563C, 0x38800000); // r_vsync 0
		Util::Hook::SetValue(0x822D9B88, 0x38800000); // com_maxfps 0

		// access to the mp menus
		// TODO: private matches dont work as intended
		Util::Hook::SetValue(0x823A1358, 0x38800001); // xblive_playEvenIfDown 1

		// kill com_statmon, it looks ugly
		Util::Hook::SetValue(0x822D9C68, 0x38800000);
		Util::Hook::SetValue(0x824D6AE4, 0x38800000);

		// set cg_debugInfoCornerOffset to be 1, 1 so it looks nicer
		Util::Hook::SetValue<uint32_t>(0x8214C56C, 0xFC400090);
		Util::Hook::SetValue<uint32_t>(0x8214C574, 0xFC200090);
	}

	void RegisterHooks()
	{
		// print all our loaded modules
		FS_InitFilesystem_Hook.Create(0x8235C2A8, FS_InitFilesystem);

		// add a nice intro movie for when the player starts the game
		Com_Init_Try_Block_Function_Hook.Create(0x822DC5A8, Com_Init_Try_Block_Function);

		// Allow unsigned fast files to load on MP
		DB_InflateInit_Hook.Create(0x821CD728, DB_InflateInit);

		// Completely disable Black Box
		Util::Hook::SetValue(0x822DC5E4, 0x60000000); // BB_Init
		Util::Hook::SetValue(0x822DD170, 0x60000000); // BB_Update

		// Completely disable Anti Cheat
		Util::Hook::SetValue(0x822DC6D4, 0x60000000); // LiveAntiCheat_Init
		Util::Hook::SetValue(0x82429348, 0x60000000); // LiveAntiCheat_Pump
		Util::Hook::SetValue(0x823A5BF4, 0x60000000); // LiveAntiCheat_Update
		Util::Hook::SetValue(0x823A44A0, 0x60000000); // LiveAntiCheat_UserSignedInToLive
		Util::Hook::SetValue(0x8225A9F8, 0x60000000); // LiveAntiCheat_UserSignedOut
		Util::Hook::SetValue(0x824290D4, 0x60000000); // LiveAntiCheat_OnChallengesReceived

		// Disable debug memory tracking
		Util::Hook::SetValue(0x823A6270, 0x60000000); // track_init

		// set build version to mine!
		getBuildNumber_Hook.Create(0x822BDA28, getBuildNumber);

		// fix console input
		Util::Hook::SetValue(0x823A0914, 0x60000000);

		// remove xray material from the scoreboard - temp fix for now, need to figure out why it's covering almost the full screen
		Util::Hook::SetValue(0x821637A4, 0x60000000);

		Cmd_Init_Hook.Create(0x822CA580, Cmd_Init);

		StringEdits();
		DVarEdits();
	}

	void UnregisterHooks()
	{
		Com_Init_Try_Block_Function_Hook.Clear();
		DB_InflateInit_Hook.Clear();
		getBuildNumber_Hook.Clear();
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
