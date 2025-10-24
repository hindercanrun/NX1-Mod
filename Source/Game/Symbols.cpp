namespace Symbols
{
	namespace SP_Dev
	{
		// functions

		Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x824221C8);
		Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x82421160);

		Com_Printf_t Com_Printf = Com_Printf_t(0x82427A50);

		Con_IsActive_t Con_IsActive = Con_IsActive_t(0x8220CDB8);
		Con_CheckResize_t Con_CheckResize = Con_CheckResize_t(0x822072D0);
		Con_DrawSolidConsole_t Con_DrawSolidConsole = Con_DrawSolidConsole_t(0x8220E9D0);

		DevGui_IsActive_t DevGui_IsActive = DevGui_IsActive_t(0x8229CB50);

		Dvar_FindVar_t Dvar_FindVar = Dvar_FindVar_t(0x824D98C8);

		Key_IsCatcherActive_t Key_IsCatcherActive = Key_IsCatcherActive_t(0x82217FB0);

		R_AddCmdDrawText_t R_AddCmdDrawText = R_AddCmdDrawText_t(0x826FCB00);

		Sys_Milliseconds_t Sys_Milliseconds = Sys_Milliseconds_t(0x825248B8);
		Sys_MillisecondsRaw_t Sys_MillisecondsRaw = Sys_MillisecondsRaw_t(0x82524918);

		// variables

		Structs::CmdArgs* cmd_args = (Structs::CmdArgs*)0x83A76D48;

		Structs::DWLogonStatus* g_LogOnStatus = (Structs::DWLogonStatus*)0x852A96EC;

		Structs::GamerSettingState* gamerSettings = (Structs::GamerSettingState*)0x82B0EC48;
		unsigned int* g_playStartTime = (unsigned int*)0x82B11ED0;

		Structs::ScreenPlacement* scrPlaceFull = (Structs::ScreenPlacement*)0x82B15C08;
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
		Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x822C96F8);
		Cmd_FindCommand_t Cmd_FindCommand = Cmd_FindCommand_t(0x822C9698);
		Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x822C8C20);

		CL_ConsolePrint_t CL_ConsolePrint = CL_ConsolePrint_t(0x8218F058);

		DB_AuthLoad_InflateInit_t DB_AuthLoad_InflateInit = DB_AuthLoad_InflateInit_t(0x821CC670);
		DB_LoadXAssets_t DB_LoadXAssets = DB_LoadXAssets_t(0x82213570);

		Dvar_ValueToString_t Dvar_ValueToString = Dvar_ValueToString_t(0x82372F70);
		Dvar_IsCheatProtected_t Dvar_IsCheatProtected = Dvar_IsCheatProtected_t(0x82372920);

		Sys_Milliseconds_t Sys_Milliseconds = Sys_Milliseconds_t(0x823A6C20);

		Structs::DBLoadData* g_load = (Structs::DBLoadData*)0x8283DA90;
	}
}
