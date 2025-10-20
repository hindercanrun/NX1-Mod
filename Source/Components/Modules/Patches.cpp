namespace Patches
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Util::Hook::Detour FS_InitFilesystem_Hook;
		void FS_InitFilesystem()
		{
			DWORD start = GetTickCount(); // We could use Sys_Milliseconds here buuut GetTickCount works fine

			Symbols::SP_Dev::Com_Printf(0, "\nLoading modules...\n");
			for (int i = 0; i < Loader::g_moduleCount; ++i)
			{
				Symbols::SP_Dev::Com_Printf(0, "%d: %s\n", i + 1, Loader::g_modules[i].name);
			}
		
			DWORD end = GetTickCount();
			DWORD duration = end - start;

			Symbols::SP_Dev::Com_Printf(0, "Loaded all modules in %lu ms\n\n", duration);

			auto Invoke = FS_InitFilesystem_Hook.Invoke<void(*)()>();
			Invoke();
		}

		Util::Hook::Detour Com_ExecStartupConfigs_Hook;
		void Com_ExecStartupConfigs(int localClientNum, const char* configFile)
		{
			static bool alreadyRanFunction = FALSE;
			if (alreadyRanFunction)
			{
				return;
			}
			alreadyRanFunction = TRUE;

			auto Invoke = Com_ExecStartupConfigs_Hook.Invoke<void(*)(int, const char*)>();
			Invoke(localClientNum, configFile);
		}

		Util::Hook::Detour COM_PlayIntroMovies_Hook;
		void COM_PlayIntroMovies()
		{
			Symbols::SP_Dev::Cbuf_AddText(0, "autocinematic title\n");
		}

		Util::Hook::Detour getBuildNumber_Hook;
		const char* getBuildNumber()
		{
			return Util::String::Va("NX1-Mod");
		}

		Util::Hook::Detour LSP_CheckOngoingTasks_Hook;
		void LSP_CheckOngoingTasks(int PacketsInternal)
		{
			// null stub
		}

		Util::Hook::Detour MAssertVargs_Hook;
		int MAssertVargs(const char* filename, int line, int type, int, const char* fmt, ...)
		{
			// TODO: Implement symbols printing. For that extra cool debug info

			static const char* lastFilename = nullptr;
			static int lastLine = -1;
			static int repeatCount = 0;

			// Check if this is the same assert location as last time
			if (lastFilename && strcmp(lastFilename, filename) == 0 && lastLine == line)
			{
				repeatCount++;
			}
			else
			{
				lastFilename = filename;
				lastLine = line;
				repeatCount = 1;
			}

			char message[1024];

			va_list va;
			va_start(va, fmt);
			_vsnprintf_s(message, sizeof(message), fmt, va);
			message[sizeof(message) - 1] = '\0';

			Symbols::SP_Dev::Com_Printf(0, "\n");
			Symbols::SP_Dev::Com_Printf(0, "****************************************\n");
			Symbols::SP_Dev::Com_Printf(0, "*  Assertion Info:\n");
			Symbols::SP_Dev::Com_Printf(0, "*  Message:       %s\n", message);
			Symbols::SP_Dev::Com_Printf(0, "*  File:          %s\n", filename);
			Symbols::SP_Dev::Com_Printf(0, "*  Line:          %d\n", line);
			Symbols::SP_Dev::Com_Printf(0, "****************************************\n");

			if (repeatCount >= 2)
			{
				Symbols::SP_Dev::Com_Printf(0, "*  Warning:       Same assert triggered multiple times.\n");
				Symbols::SP_Dev::Com_Printf(0, "****************************************\n");
				return 0;
			}
			else
			{
				Symbols::SP_Dev::Com_Printf(0, "*  Note:          First time this assert occurred.\n");
				Symbols::SP_Dev::Com_Printf(0, "****************************************\n");
				return 0;
			}
		}

		void Hooks()
		{
			MAssertVargs_Hook.Create(0x824BCD10, MAssertVargs);

			Util::Hook::SetValue(0x824CF6C0, 0x60000000);

			// issue fix: disable Black Box
			Util::Hook::SetValue(0x8242C930, 0x60000000); // BB_Init
			Util::Hook::SetValue(0x8242D4F8, 0x60000000); // BB_Update

			// disable Anti Cheat
			Util::Hook::SetValue(0x8242CA38, 0x60000000); // LiveAntiCheat_Init
			Util::Hook::SetValue(0x825CD3F8, 0x60000000); // LiveAntiCheat_Pump
			Util::Hook::SetValue(0x825225D4, 0x60000000); // LiveAntiCheat_Update
			Util::Hook::SetValue(0x82521740, 0x60000000); // LiveAntiCheat_UserSignedInToLive
			Util::Hook::SetValue(0x8252119C, 0x60000000); // LiveAntiCheat_UserSignedOut
			Util::Hook::SetValue(0x825CD10C, 0x60000000); // LiveAntiCheat_OnChallengesReceived

			// print all our loaded modules
			FS_InitFilesystem_Hook.Create(0x824C34F0, FS_InitFilesystem);

			// prevent dupe config executions
			Com_ExecStartupConfigs_Hook.Create(0x824296C0, Com_ExecStartupConfigs);

			// play our own intro movie
			COM_PlayIntroMovies_Hook.Create(0x82428EF0, COM_PlayIntroMovies);

			// remove annoying "  dvar set" print
			Util::Hook::SetValue(0x824D920C, 0x60000000);

			// xenia bug fix: fix console input
			Util::Hook::SetValue(0x8251E97C, 0x60000000);

			// set build version to mine!
			getBuildNumber_Hook.Create(0x82410188, getBuildNumber);

			// dont check any lsp tasks
			LSP_CheckOngoingTasks_Hook.Create(0x825A2C68, LSP_CheckOngoingTasks);

			// remove autoexec dev
			Util::Hook::SetValue(0x8222CC84, 0x60000000);
			Util::Hook::SetValue(0x82429748, 0x60000000);
		}

		void AssertRemovals()
		{
			Util::Hook::SetValue(0x824F35F0, 0x60000000);
			Util::Hook::SetValue(0x824F3D5C, 0x60000000);
			Util::Hook::SetValue(0x824F3ABC, 0x60000000);
			Util::Hook::SetValue(0x824F3858, 0x60000000);
		}

		void StringEdits()
		{
			// example:
			// Util::Hook::SetString(<address>, <string>); // <comment> (optional)

			Util::Hook::SetString(0x8201F030, "%s> "); // uhh just make NX1-Mod look nicer
			Util::Hook::SetString(0x8201F03C, "NX1-Mod"); // NX1 GAMING !!!!!!
			Util::Hook::SetString(0x8201EEC4, "Build 1866586"); // shorten that string!
			Util::Hook::SetString(0x82076B88, "");
		}

		void DVarEdits()
		{
			// example:
			// Util::Hook::SetValue<type (if needed)>(<address>, <value>); // <comment> (optional)

			// skip main_lockout menu
			Util::Hook::SetValue(0x8242CDB8, 0x38800001); // ui_skipMainLockout

			Util::Hook::SetValue(0x827014DC, 0x38800000); // r_vsync 0
			Util::Hook::SetValue(0x82428FD0, 0x38800000); // com_maxfps 0

			// kill com_statmon, it looks ugly
			Util::Hook::SetValue(0x82702E54, 0x38800000);
			Util::Hook::SetValue(0x824290F8, 0x38800000);

			// kill view pos
			Util::Hook::SetValue(0x821BB110, 0xFC400090);
		}

		void ClearHooks()
		{
			FS_InitFilesystem_Hook.Clear();
			Com_ExecStartupConfigs_Hook.Clear();
			COM_PlayIntroMovies_Hook.Clear();
			getBuildNumber_Hook.Clear();
			LSP_CheckOngoingTasks_Hook.Clear();
		}
#endif
	}

	namespace MP_Dev
	{
		// TODO
	}

	namespace SP_Demo
	{
		// TODO
	}

	namespace MP_Demo
	{
#ifdef MP_DEMO
		Util::Hook::Detour FS_InitFilesystem_Hook;
		void FS_InitFilesystem()
		{
			DWORD start = GetTickCount(); // We could use Sys_Milliseconds here buuut GetTickCount works fine

			Util::Print::Printf("\nLoading modules...\n");
			for (int i = 0; i < Loader::g_moduleCount; ++i)
			{
				Util::Print::Printf("%d: %s\n", i + 1, Loader::g_modules[i].name);
			}
		
			DWORD end = GetTickCount();
			DWORD duration = end - start;

			Util::Print::Printf("Loaded all modules in %lu ms\n\n", duration);

			auto Invoke = FS_InitFilesystem_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void PlayIntroMovie()
		{
			Symbols::MP_Demo::Cbuf_AddText(0, "autocinematic title\n");
		}

		Util::Hook::Detour Com_Init_Try_Block_Function_Hook;
		void Com_Init_Try_Block_Function(const char* p_command_line)
		{
			auto Invoke = Com_Init_Try_Block_Function_Hook.Invoke<void(*)(const char*)>();
			Invoke(p_command_line);

			PlayIntroMovie();
		}

		Util::Hook::Detour DB_InflateInit_Hook;
		void DB_InflateInit(int fileIsSecure)
		{
			Symbols::MP_Demo::DB_AuthLoad_InflateInit(&Symbols::MP_Demo::g_load->stream, fileIsSecure, Symbols::MP_Demo::g_load->p_file->name);
		}

		Util::Hook::Detour getBuildNumber_Hook;
		const char* getBuildNumber()
		{
			return Util::String::Va("NX1-Mod");
		}

		void Cmd_LoadZone_f()
		{
			Structs::XZoneInfo zoneInfo;

			zoneInfo.allocFlags = 1;
			zoneInfo.name = "ui"; // TODO: don't hardcode zone name
			zoneInfo.freeFlags = 0;

			Symbols::MP_Demo::DB_LoadXAssets(&zoneInfo, 1, 1);
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

		void Hooks()
		{
			// issue fix: disable Black Box
			Util::Hook::SetValue(0x822DC5E4, 0x60000000); // BB_Init
			Util::Hook::SetValue(0x822DD170, 0x60000000); // BB_Update

			// disable Anti Cheat
			Util::Hook::SetValue(0x822DC6D4, 0x60000000); // LiveAntiCheat_Init
			Util::Hook::SetValue(0x82429348, 0x60000000); // LiveAntiCheat_Pump
			Util::Hook::SetValue(0x823A5BF4, 0x60000000); // LiveAntiCheat_Update
			Util::Hook::SetValue(0x823A44A0, 0x60000000); // LiveAntiCheat_UserSignedInToLive
			Util::Hook::SetValue(0x8225A9F8, 0x60000000); // LiveAntiCheat_UserSignedOut
			Util::Hook::SetValue(0x824290D4, 0x60000000); // LiveAntiCheat_OnChallengesReceived

			// print all our loaded modules
			FS_InitFilesystem_Hook.Create(0x8235C2A8, FS_InitFilesystem);

			// add a nice intro movie for when the game starts
			Com_Init_Try_Block_Function_Hook.Create(0x822DC5A8, Com_Init_Try_Block_Function);

			// allow unsigned fast files to load on MP
			DB_InflateInit_Hook.Create(0x821CD728, DB_InflateInit);

			// xenia bug fix: fix console input
			Util::Hook::SetValue(0x823A0914, 0x60000000);

			// bug fix: remove xray material from the scoreboard
			Util::Hook::SetValue(0x821637A4, 0x60000000);

			// set build version to mine!
			getBuildNumber_Hook.Create(0x822BDA28, getBuildNumber);

			// init our custom cmds
			Cmd_Init_Hook.Create(0x822CA580, Cmd_Init);
		}

		void StringEdits()
		{
			// example:
			// Util::Hook::SetString(<address>, <string>); // <comment> (optional)

			Util::Hook::SetString(0x820195A8, "%s> "); // uhh just make NX1-MOD look nicer
			Util::Hook::SetString(0x820195B4, "NX1-Mod"); // NX1 GAMING !!!!!!
			Util::Hook::SetString(0x8201953C, "Build 1866586"); // shorten that string!
		}

		void DVarEdits()
		{
			// example:
			// Util::Hook::SetValue<type (if needed)>(<address>, <value>); // <comment> (optional)

			Util::Hook::SetValue(0x824D563C, 0x38800000); // r_vsync 0
			Util::Hook::SetValue(0x822D9B88, 0x38800000); // com_maxfps 0

			// allow access to the MP menus
			// TODO: private matches dont work as intended
			Util::Hook::SetValue(0x823A1358, 0x38800001); // xblive_playEvenIfDown 1

			// kill com_statmon, it looks ugly
			Util::Hook::SetValue(0x822D9C68, 0x38800000);
			Util::Hook::SetValue(0x824D6AE4, 0x38800000);

			// set cg_debugInfoCornerOffset to be 1, 1 so it looks nicer
			Util::Hook::SetValue<uint32_t>(0x8214C56C, 0xFC400090);
			Util::Hook::SetValue<uint32_t>(0x8214C574, 0xFC200090);
		}

		void ClearHooks()
		{
			FS_InitFilesystem_Hook.Clear();
			Com_Init_Try_Block_Function_Hook.Clear();
			DB_InflateInit_Hook.Clear();
			getBuildNumber_Hook.Clear();
			Cmd_Init_Hook.Clear();
		}
#endif
	}

	void Load()
	{
#ifdef SP_DEV
		SP_Dev::Hooks();
		SP_Dev::AssertRemovals();
		SP_Dev::StringEdits();
		SP_Dev::DVarEdits();
#elif MP_DEMO
		MP_Demo::Hooks();
		MP_Demo::StringEdits();
		MP_Demo::DVarEdits();
#endif
	}

	void Unload()
	{
#ifdef SP_DEV
		SP_Dev::ClearHooks();
#elif MP_DEMO
		MP_Demo::ClearHooks();
#endif
	}
}
