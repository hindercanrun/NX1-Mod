#pragma once

namespace Util
{
	namespace FileSystem
	{
		bool WriteFileToDisk(const char* filePath, const char* data, size_t dataSize);
		char* ReadFileToString(const char* filePath);
		bool FileExists(const char* filePath);

		inline bool CreateDirectoryRecursive(const char* path)
		{
			if (!path || !*path)
				return false;

			std::string fullPath(path);
			for (size_t i = 0; i < fullPath.length(); ++i)
			{
				if (fullPath[i] == '\\' || fullPath[i] == '/')
				{
					char old = fullPath[i];
					fullPath[i] = 0; // temporarily terminate string
					CreateDirectoryA(fullPath.c_str(), nullptr);
					fullPath[i] = old; // restore
				}
			}

			// final call for the full path itself
			return CreateDirectoryA(fullPath.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
		}
	}
}