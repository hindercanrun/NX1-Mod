#include "../Std_Include.h"
#include "Symbols.h"

namespace Symbols
{
	Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x822C96F8);
	Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x822C8C20);

	CL_ConsolePrint_t CL_ConsolePrint = CL_ConsolePrint_t(0x8218F058);

	DB_AuthLoad_InflateInit_t DB_AuthLoad_InflateInit = DB_AuthLoad_InflateInit_t(0x821CC670);
	DB_GetXAssetTypeName_t DB_GetXAssetTypeName = DB_GetXAssetTypeName_t(0x821CBC90);
	DB_GetXAssetTypeSize_t DB_GetXAssetTypeSize = DB_GetXAssetTypeSize_t(0x821CBC78);
	DB_GetXAssetName_t DB_GetXAssetName = DB_GetXAssetName_t(0x821CBC90);

	Structs::DBLoadData* g_load = (Structs::DBLoadData*)0x8283DA90;
	const char* g_assetNames = (const char*)0x82578918;
}
