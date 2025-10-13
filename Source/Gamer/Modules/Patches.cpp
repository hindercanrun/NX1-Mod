#include "../Std_Include.h"

namespace Patches
{
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

	static FILE* g_consoleLog = NULL;

	void OpenLogFile()
	{
		if (g_consoleLog)
			return;

		g_consoleLog = fopen("game:/nx1gaming/console.log", "w");
		if (!g_consoleLog)
			return;

		time_t now = time(NULL);
		struct tm* t = localtime(&now);
		if (t)
		{
			fprintf(g_consoleLog, "logfile opened on %s\n", asctime(t));
		}

		fflush(g_consoleLog);
	}

	void LogPrintMessage(const char* msg)
	{
		if (!g_consoleLog)
			OpenLogFile();

		if (g_consoleLog)
		{
			fprintf(g_consoleLog, "%s", msg);
			fflush(g_consoleLog);
		}
	}

	void PrintMessage(const char* msg)
	{
		if (msg[0] == '^' && msg[1] != '\0')
			msg += 2;

		Symbols::CL_ConsolePrint(0, 0, msg, 0, 0, 0);

		LogPrintMessage(msg);
	}

	Util::Hook::Detour getBuildNumber_Hook;
	const char* getBuildNumber()
	{
		return Util::String::va("1 01/05/2012 11:39:15 NX1GAMING");
	}

	void RegisterHooks()
	{
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

		Util::Hook::SetValue(0x8253DFA8, PrintMessage);

		// set version to mine!
		getBuildNumber_Hook.Create(0x822BDA28, getBuildNumber);

		// fix console input
		Util::Hook::SetValue(0x823A0914, 0x60000000);

		// remove xray material from the scoreboard
		Util::Hook::SetValue(0x821637A4, 0x60000000);

		// Disable debug memory tracking
		Util::Hook::SetValue(0x823A6270, 0x60000000); // track_init

		*(char*)0x82019534 = '\0'; // Remove 'Build 445 xenon' from the console window as it's not needed

		// Below are just your general string edits.
		// Example:
		// Util::Hook::SetString(<address>, <string>); // <comment> (optional)

		Util::Hook::SetString(0x820195B4, "NX1 GAMING "); // NX1 GAMER !!!!!!
		Util::Hook::SetString(0x8201953C, "Build 1866586"); // shorten that string!

		// Below are just your general dvar value edits.
		// Example:
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

	void UnregisterHooks()
	{
		DB_InflateInit_Hook.Clear();
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
