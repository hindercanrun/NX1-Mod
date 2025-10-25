#pragma once

namespace Symbols
{
	namespace SP_Dev
	{
		typedef void (*Cmd_AddCommand_t)(const char* cmdName, void (__cdecl* function)(), Structs::cmd_function_s* allocedCmd);
		extern Cmd_AddCommand_t Cmd_AddCommand;

		typedef void (*Cbuf_AddText_t)(int localClientNum, const char* text);
		extern Cbuf_AddText_t Cbuf_AddText;

		typedef void (*Com_Printf_t)(int channel, const char* fmt, ...);
		extern Com_Printf_t Com_Printf;

		typedef void (*CL_ConsolePrint_t)(int localClientNum, int channel, const char* txt, int duration, int pixelWidth, int flags);
		extern CL_ConsolePrint_t CL_ConsolePrint;

		typedef BOOL (*Con_IsActive_t)(int localClientNum);
		extern Con_IsActive_t Con_IsActive;

		typedef void (*Con_CheckResize_t)(const Structs::ScreenPlacement* scrPlace);
		extern Con_CheckResize_t Con_CheckResize;

		typedef void (*Con_DrawSolidConsole_t)(int localClientNum);
		extern Con_DrawSolidConsole_t Con_DrawSolidConsole;

		typedef BOOL (*DevGui_IsActive_t)();
		extern DevGui_IsActive_t DevGui_IsActive;

		typedef BOOL (*Key_IsCatcherActive_t)(int localClientNum, int mask);
		extern Key_IsCatcherActive_t Key_IsCatcherActive;

		typedef void (*I_strncpyz_t)(char* dest, const char* src, int destsize);
		extern I_strncpyz_t I_strncpyz;

		typedef const char* (*I_stristr_t)(const char* s0, const char* substr);
		extern I_stristr_t I_stristr;

		typedef void (*R_AddCmdDrawText_t)(const char* text, int maxChars, Structs::Font_s* font, float x, float y, float xScale, float yScale, float rotation, const float* colour, int style, Structs::EScreenLayer layer);
		extern R_AddCmdDrawText_t R_AddCmdDrawText;

		extern Structs::CmdArgs* cmd_args;

		extern Structs::ScreenPlacement* scrPlaceFull;
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
		typedef void (*Cmd_AddCommand_t)(const char* cmdName, void (__cdecl* function)(), Structs::cmd_function_s* allocedCmd);
		extern Cmd_AddCommand_t Cmd_AddCommand;

		typedef Structs::cmd_function_s* (*Cmd_FindCommand_t)(const char* cmdName);
		extern Cmd_FindCommand_t Cmd_FindCommand;

		typedef void (*Cbuf_AddText_t)(int localClientNum, const char* text);
		extern Cbuf_AddText_t Cbuf_AddText;

		typedef void (*CL_ConsolePrint_t)(int localClientNum, int channel, const char* txt, int duration, int pixelWidth, int flags);
		extern CL_ConsolePrint_t CL_ConsolePrint;

		typedef HRESULT (*DB_AuthLoad_InflateInit_t)(Structs::db_z_stream_s* stream, int isSecure, const char* filename);
		extern DB_AuthLoad_InflateInit_t DB_AuthLoad_InflateInit;

		typedef void (*DB_LoadXAssets_t)(Structs::XZoneInfo* zoneInfo, unsigned int zoneCount, unsigned int syncMode);
		extern DB_LoadXAssets_t DB_LoadXAssets;

		typedef const char* (*Dvar_ValueToString_t)(const Structs::dvar_t* dvar, Structs::DvarValue value);
		extern Dvar_ValueToString_t Dvar_ValueToString;

		typedef int (*Dvar_IsCheatProtected_t)(unsigned short flags);
		extern Dvar_IsCheatProtected_t Dvar_IsCheatProtected;

		typedef DWORD (*Sys_Milliseconds_t)();
		extern Sys_Milliseconds_t Sys_Milliseconds;

		extern Structs::DBLoadData* g_load;
	}
}
