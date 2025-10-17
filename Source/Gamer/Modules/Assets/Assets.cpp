#include <map>

namespace Assets
{
	const char* LocalizedStrings_GetFileNotes(const std::string& prefix)
	{
		if (prefix == "debug")
			return "Strings used for debugging go in this file.";
		else if (prefix == "game")
			return "Game messages made by the server game dll go in this file.";
		else if (prefix == "menu")
			return "Strings displayed in the menus go in this file.";
		else if (prefix == "script")
			return "All game messages made by script should go in this file.";
		else if (prefix == "weapon")
			return "Strings used in the weapon settings go in this file.";
		return ""; // no known strings
	}

	Util::Hook::Detour Load_LocalizeEntryPtr_Hook;
	void Load_LocalizeEntryPtr(bool atStreamStart)
	{
		auto Invoke = Load_LocalizeEntryPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		LocalizeEntry** varLocalizeEntryPtr = *(LocalizeEntry***)0x828BEB5C;
		if (!varLocalizeEntryPtr || !*varLocalizeEntryPtr)
			return;

		LocalizeEntry* entry = *varLocalizeEntryPtr;
		if (!entry->name)
			return;

		std::string name(entry->name);
		std::string value(entry->value);

		std::string prefix = "default";
		std::string key = name;

		size_t underscore = name.find('_');
		if (underscore != std::string::npos)
		{
			prefix = name.substr(0, underscore);
			key = name.substr(underscore + 1);
		}

		std::transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);
		std::string outPath = "game:\\nx1-data\\dump\\localizedstrings\\" + prefix + ".str";
		FILE* f = fopen(outPath.c_str(), "ab+");
		if (!f)
			return;

		const char* fileNotes = LocalizedStrings_GetFileNotes(prefix);

		fseek(f, 0, SEEK_END);
		long size = ftell(f);
		if (size == 0)
		{
			fprintf(f,
				"// Note to translators:\n"
				"// If a sentence is the same in your language then please change it to \"#same\"\n"
				"//\n"
				"// eg:\n"
				"// LANG_ENGLISH  \"HALT\"\n"
				"// LANG_GERMAN   \"#same\"\n"
				"//\n"
				"// (This is so we can tell which strings have been signed-off as ok to be the same words for QA\n"
				"//  and because we do not store duplicate strings, which will then get exported again next time\n"
				"//  as being untranslated.)\n"
				"//\n"
				"VERSION             \"1\"\n"
				"CONFIG              \"C:\\trees\\nx1\\bin\\StringEd.cfg\"\n"
				"FILENOTES           \"%s\"\n\n",
				fileNotes);
		}

		std::string escapedValue = value;
		size_t pos = 0;
		while ((pos = escapedValue.find('"', pos)) != std::string::npos)
		{
			escapedValue.insert(pos, "\"");
			pos += 2;
		}

		fprintf(f, "REFERENCE           %s\n", key.c_str());
		fprintf(f, "LANG_ENGLISH        \"%s\"\n\n", escapedValue.c_str());

		fclose(f);
	}

	Util::Hook::Detour DB_GetRawBuffer_Hook;
	void DB_GetRawBuffer(const RawFile* rawFile, char* buffer, int size)
	{
		auto Invoke = DB_GetRawBuffer_Hook.Invoke<void(*)(const RawFile*, char*, int)>();

		// TODO: put this behind a dvar
		// override the file if it exists
		RawFile* loaded = LoadRawFiles(rawFile->name);
		if (loaded)
		{
			int copySize = (size < loaded->len) ? size : loaded->len;
			memcpy(buffer, loaded->buffer, copySize);

			FreeRawFiles(loaded);
			return;
		}

		// TODO: put this behind a dvar
		//DumpRawFiles(rawFile, buffer, size);

		Invoke(rawFile, buffer, size);
	}

	Util::Hook::Detour Load_StringTablePtr_Hook;
	void Load_StringTablePtr(bool atStreamStart)
	{
		auto Invoke = Load_StringTablePtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		StringTable** varStringTablePtr = *(StringTable***)0x828BE15C;

		if (varStringTablePtr && *varStringTablePtr)
		{
			StringTable* varStringTable = *varStringTablePtr;

			std::string assetName = varStringTable->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string csvTable;
			for (int j = 0; j < varStringTable->rowCount; j++)
			{
				for (int k = 0; k < varStringTable->columnCount; k++)
				{
					csvTable += varStringTable->values[j * varStringTable->columnCount + k].string;
					if (k < varStringTable->columnCount - 1)
					{
						csvTable += ",";
					}
				}
				csvTable += "\n";
			}

			std::string outPath = "game:\\nx1-data\\dump\\" + assetName;
			Util::FileSystem::WriteFileToDisk(outPath.c_str(), csvTable.c_str(), csvTable.size());
		}
	}

	Util::Hook::Detour Load_ShellshockParamsPtr_Hook;
	void Load_ShellshockParamsPtr(bool atStreamStart)
	{
		auto Invoke = Load_ShellshockParamsPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		ShellShockParams** varShellshockParamsPtr = *(ShellShockParams***)0x828BE780;

		if (varShellshockParamsPtr && *varShellshockParamsPtr)
		{
			Dump_ShellShock(*varShellshockParamsPtr);
		}
	}

	Util::Hook::Detour Load_FogDefPtr_Hook;
	void Load_FogDefPtr(bool atStreamStart)
	{
		auto Invoke = Load_FogDefPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		FogDef** varFogDefPtr = *(FogDef***)0x828BE124;

		if (varFogDefPtr && *varFogDefPtr)
		{
			Dump_FogDef(*varFogDefPtr);
		}
	}

	void Hooks()
	{
		DB_GetRawBuffer_Hook.Create(0x822140E0, DB_GetRawBuffer);
		//Load_StringTablePtr_Hook.Create(0x821F2F18, Load_StringTablePtr);
		//Load_LocalizeEntryPtr_Hook.Create(0x821EFC90, Load_LocalizeEntryPtr);
		//Load_ShellshockParamsPtr_Hook.Create(0x821FB5D0, Load_ShellshockParamsPtr);
		//
		//
		//Load_FogDefPtr_Hook.Create(0x821F5488, Load_FogDefPtr);
	}

	void Load()
	{
		Hooks();
	}

	void Unload()
	{
	}
}
