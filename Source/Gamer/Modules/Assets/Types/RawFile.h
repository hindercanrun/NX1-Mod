#pragma once

namespace Assets
{
	struct RawFile
	{
		const char* name;
		int compressedLen;
		int len;
		const char* buffer;
	};

	RawFile* LoadRawFiles(const char* name);
	void DumpRawFiles(const RawFile* rawFile, char* buffer, int size);
}
