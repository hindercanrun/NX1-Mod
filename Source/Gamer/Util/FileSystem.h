#pragma once

namespace Util
{
	namespace FileSystem
	{
		bool WriteFileToDisk(const char* filePath, const char* data, size_t dataSize);
		char* ReadFileToString(const char* filePath);
		bool FileExists(const char* filePath);
	}
}