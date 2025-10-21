namespace Symbols
{
	namespace SP_Dev
	{
		Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x822C96F8);
		Cmd_FindCommand_t Cmd_FindCommand = Cmd_FindCommand_t(0x822C9698);
		Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x82421160);

		Com_Printf_t Com_Printf = Com_Printf_t(0x82427A50);

		CL_ConsolePrint_t CL_ConsolePrint = CL_ConsolePrint_t(0x8218F058);
		Con_CheckResize_t Con_CheckResize = Con_CheckResize_t(0x822072D0);
		Con_DrawSolidConsole_t Con_DrawSolidConsole = Con_DrawSolidConsole_t(0x8220E9D0);

		DB_AuthLoad_InflateInit_t DB_AuthLoad_InflateInit = DB_AuthLoad_InflateInit_t(0x821CC670);
		DB_LoadXAssets_t DB_LoadXAssets = DB_LoadXAssets_t(0x82213570);

		Dvar_ValueToString_t Dvar_ValueToString = Dvar_ValueToString_t(0x82372F70);
		Dvar_IsCheatProtected_t Dvar_IsCheatProtected = Dvar_IsCheatProtected_t(0x82372920);

		Key_IsCatcherActive_t Key_IsCatcherActive = Key_IsCatcherActive_t(0x82217FB0);

		R_AddCmdDrawText_t R_AddCmdDrawText = R_AddCmdDrawText_t(0x826FCB00);

		Sys_Milliseconds_t Sys_Milliseconds = Sys_Milliseconds_t(0x823A6C20);

		Structs::DBLoadData* g_load = (Structs::DBLoadData*)0x8283DA90;

		Structs::ScreenPlacement* scrPlaceFull = (Structs::ScreenPlacement*)0x82B15C08;
	}

	namespace MP_Dev
	{
	}

	namespace SP_Demo
	{
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
