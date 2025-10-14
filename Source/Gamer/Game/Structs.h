#pragma once

namespace Structs
{
	struct cmd_function_s
	{
		cmd_function_s* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void (__cdecl* function)();
	};

	enum DvarSetSource : __int32
	{
		DVAR_SOURCE_INTERNAL = 0x0,
		DVAR_SOURCE_EXTERNAL = 0x1,
		DVAR_SOURCE_SCRIPT = 0x2,
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char *string;
		unsigned __int8 color[4];
	};

	const struct dvar_t
	{
		const char *name;
		const char *description;
		unsigned __int16 flags;
		unsigned __int8 type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		//todo DvarLimits domain;
		dvar_t *hashNext;
	};

	struct SysFile
	{
		void* handle;
		int startOffset;
	};

	struct DBFile
	{
		SysFile handle;
		char name[64];
	};

	struct db_internal_state
	{
		int dummy;
	};

	struct db_z_stream_s
	{
		unsigned __int8* next_in;
		unsigned int avail_in;
		unsigned int total_in;

		unsigned __int8* next_out;
		unsigned int avail_out;
		unsigned int total_out;

		char* msg;

		db_internal_state* state;

		unsigned __int8* (__fastcall* zalloc)(unsigned __int8*, unsigned int, unsigned int);
		void (__fastcall* zfree)(unsigned __int8*, unsigned __int8*);

		unsigned __int8* opaque;
		int data_type;
	};

	struct DBLoadData
	{
		DBFile* p_file;
		int outstandingRead;

		unsigned __int8* p_fileBuffer;
		unsigned int readSize;
		unsigned int completedReadSize;
		unsigned int offset;

		unsigned __int8* p_startIn;

		OVERLAPPED overlapped;

		unsigned int readError;

		db_z_stream_s stream;

		unsigned int lookaheadReadSize;
		unsigned int lookaheadOffset;
		unsigned int lookaheadClearAvailIn;
	};

	struct XZoneInfo
	{
		const char *name;
		int allocFlags;
		int freeFlags;
	};
}
