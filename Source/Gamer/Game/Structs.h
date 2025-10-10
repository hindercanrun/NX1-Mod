#pragma once

#include "../Std_Include.h"

namespace Structs
{
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
}
