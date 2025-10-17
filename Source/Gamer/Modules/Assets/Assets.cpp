#include <stdio.h>
#include <string.h>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

namespace Assets
{
	Util::Hook::Detour DB_GetRawBuffer_Hook;
	void DB_GetRawBuffer(const RawFile* rawFile, char* buffer, int size)
	{
		auto Invoke = DB_GetRawBuffer_Hook.Invoke<void(*)(const RawFile*, char*, int)>();

		RawFile* loaded = LoadRawFiles(rawFile->name);
		if (loaded)
		{
			// Make sure not to overflow the buffer
			int copySize = size < loaded->len ? size : loaded->len;
			memcpy(buffer, loaded->buffer, copySize);

			// Free the temporary loaded rawfile
			//RawFileLoader::FreeRawFile(loaded);

			return; // Loaded successfully, skip original engine call
		}

		//RawFile::DumpRawFiles(rawFile, buffer, size);

		Invoke(rawFile, buffer, size);
	}

	void Hooks()
	{
		DB_GetRawBuffer_Hook.Create(0x822140E0, DB_GetRawBuffer);
	}

	void Load()
	{
		Hooks();
	}

	void Unload()
	{
	}
}
