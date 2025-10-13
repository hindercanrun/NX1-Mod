#pragma once

namespace Symbols
{
	typedef void (*Cmd_AddCommand_t)(const char* cmdName, void (__cdecl* function)(), Structs::cmd_function_s* allocedCmd);
	extern Cmd_AddCommand_t Cmd_AddCommand;

	typedef void (*Cbuf_AddText_t)(int localClientNum, const char* text);
	extern Cbuf_AddText_t Cbuf_AddText;

	typedef void (*CL_ConsolePrint_t)(int localClientNum, int channel, const char* txt, int duration, int pixelWidth, int flags);
	extern CL_ConsolePrint_t CL_ConsolePrint;

	typedef HRESULT (*DB_AuthLoad_InflateInit_t)(Structs::db_z_stream_s* stream, int isSecure, const char* filename);
	extern DB_AuthLoad_InflateInit_t DB_AuthLoad_InflateInit;

	typedef const char* (*DB_GetXAssetTypeName_t)(int type);
	extern DB_GetXAssetTypeName_t DB_GetXAssetTypeName;

	typedef int (*DB_GetXAssetTypeSize_t)(int type);
	extern DB_GetXAssetTypeSize_t DB_GetXAssetTypeSize;

	typedef const char* (*DB_GetXAssetName_t)(const Structs::XAsset* asset);
	extern DB_GetXAssetName_t DB_GetXAssetName;

	extern Structs::DBLoadData* g_load;
	extern const char* g_assetNames;
}
