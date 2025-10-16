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

	enum DvarSetSource
	{
		DVAR_SOURCE_INTERNAL,
		DVAR_SOURCE_EXTERNAL,
		DVAR_SOURCE_SCRIPT,
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		unsigned char color[4];
	};

	struct EnumLimit
	{
		int stringCount;
		const char** strings;
	};

	struct IntLimit
	{
		int min;
		int max;
	};

	struct FloatLimit
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		EnumLimit enumeration;
		IntLimit integer;
		FloatLimit value;
		FloatLimit vector;
	};

	struct dvar_t
	{
		const char* name;
		const char* description;
		unsigned int flags;
		char type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		dvar_t* hashNext;
	};

	struct SysFile
	{
		HANDLE handle;
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

	typedef struct
	{
		Bytef* next_in; /* next input byte */
		uInt avail_in;  /* number of bytes available at next_in */
		uInt total_in;  /* total number of input bytes read so far */

		unsigned __int8* next_out; /* next output byte will go here */
		uInt avail_out; /* remaining free space at next_out */
		uInt total_out; /* total number of bytes output so far */

		char* msg; /* last error message, NULL if no error */

		db_internal_state* state; /* not visible by applications */

		alloc_func zalloc;  /* used to allocate the internal state */
		free_func  zfree;   /* used to free the internal state */
		voidpf opaque; /* private data object passed to zalloc and zfree */

		int data_type; /* best guess about the data type: binary or text for deflate, or the decoding state for inflate */
	} db_z_stream_s;

	struct DBLoadData
	{
		DBFile* p_file;
		int outstandingRead;

		Bytef* p_fileBuffer;
		uInt readSize;
		uInt completedReadSize;
		uInt offset;

		Bytef* p_startIn;

		OVERLAPPED overlapped;

		uInt readError;

		db_z_stream_s stream;

		uInt lookaheadReadSize;
		uInt lookaheadOffset;
		uInt lookaheadClearAvailIn;
	};

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};
}
