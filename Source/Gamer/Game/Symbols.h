#pragma once

namespace Symbols
{
	typedef HRESULT (*DB_AuthLoad_InflateInit_t)(Structs::db_z_stream_s* stream, int isSecure, const char* filename);
	extern DB_AuthLoad_InflateInit_t DB_AuthLoad_InflateInit;

	extern Structs::DBLoadData* g_load;
}
