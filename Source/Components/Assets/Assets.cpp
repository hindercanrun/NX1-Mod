#include "Assets.h"

namespace Assets
{
	Util::Hook::Detour Load_PhysPresetPtr_Hook;
	void Load_PhysPresetPtr(bool atStreamStart)
	{
		auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		PhysPreset** varPhysPresetPtr = *(PhysPreset***)0x82C6E7E0;

		if (varPhysPresetPtr && *varPhysPresetPtr)
		{
			Dump_PhysPreset(*varPhysPresetPtr);
		}
	}

	Util::Hook::Detour Load_MapEntsPtr_Hook;
	void Load_MapEntsPtr(bool atStreamStart)
	{
		auto Invoke = Load_MapEntsPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		MapEnts** varMapEntsPtr = *(MapEnts***)0x82C6E7F8;

		if (varMapEntsPtr && *varMapEntsPtr)
		{
			Dump_MapEnts(*varMapEntsPtr);
		}
	}

	Util::Hook::Detour Load_LocalizeEntryPtr_Hook;
	void Load_LocalizeEntryPtr(bool atStreamStart)
	{
		auto Invoke = Load_LocalizeEntryPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		LocalizeEntry** varLocalizeEntryPtr = *(LocalizeEntry***)0x82C6E95C;

		if (!varLocalizeEntryPtr || !*varLocalizeEntryPtr)
		{
			Dump_LocalizeEntry(*varLocalizeEntryPtr);
		}
	}

	Util::Hook::Detour DB_GetRawBuffer_Hook;
	void DB_GetRawBuffer(const RawFile* rawFile, char* buffer, int size)
	{
		auto Invoke = DB_GetRawBuffer_Hook.Invoke<void(*)(const RawFile*, char*, int)>();
		/*
		// TODO: put this behind a dvar
		// override the file if it exists
		RawFile* loaded = LoadRawFiles(rawFile->name);
		if (loaded)
		{
			int copySize = (size < loaded->len) ? size : loaded->len;
			memcpy(buffer, loaded->buffer, copySize);

			FreeRawFiles(loaded);
			return;
		}*/

		// TODO: put this behind a dvar
		DumpRawFiles(rawFile, buffer, size);

		Invoke(rawFile, buffer, size);
	}

	Util::Hook::Detour Load_StringTablePtr_Hook;
	void Load_StringTablePtr(bool atStreamStart)
	{
		auto Invoke = Load_StringTablePtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		StringTable** varStringTablePtr = *(StringTable***)0x82C6DF5C;

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

	Util::Hook::Detour Load_TracerDefPtr_Hook;
	void Load_TracerDefPtr(bool atStreamStart)
	{
		auto Invoke = Load_TracerDefPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		TracerDef** varTracerDefPtr = *(TracerDef***)0x82C6E834;

		if (varTracerDefPtr && *varTracerDefPtr)
		{
			//Dump_TracerDef(*varTracerDefPtr);
		}
	}

	Util::Hook::Detour Load_ShellshockParamsPtr_Hook;
	void Load_ShellshockParamsPtr(bool atStreamStart)
	{
		auto Invoke = Load_ShellshockParamsPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		ShellShockParams** varShellshockParamsPtr = *(ShellShockParams***)0x82C6E580;

		if (varShellshockParamsPtr && *varShellshockParamsPtr)
		{
			//Dump_ShellShock(*varShellshockParamsPtr);
		}
	}

	Util::Hook::Detour Load_FogDefPtr_Hook;
	void Load_FogDefPtr(bool atStreamStart)
	{
		auto Invoke = Load_FogDefPtr_Hook.Invoke<void(*)(bool)>();
		Invoke(atStreamStart);

		FogDef** varFogDefPtr = *(FogDef***)0x82C6DF24;

		if (varFogDefPtr && *varFogDefPtr)
		{
			//Dump_FogDef(*varFogDefPtr);
		}
	}

	void Hooks()
	{
		// Load_PhysPresetPtr_Hook.Create(0x82250C00, Load_PhysPresetPtr);
		// PhysCollmap
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		//
		// Load_MapEntsPtr_Hook.Create(0x82259EF0, Load_MapEntsPtr);
		//
		//
		//
		//
		//
		//
		Load_LocalizeEntryPtr_Hook.Create(0x8225FD28, Load_LocalizeEntryPtr);
		//
		//
		//
		//
		//
		// DB_GetRawBuffer_Hook.Create(0x82288630, DB_GetRawBuffer);
		// Load_StringTablePtr_Hook.Create(0x82263550, Load_StringTablePtr);
		//
		//
		Load_TracerDefPtr_Hook.Create(0x822603F0, Load_TracerDefPtr);
		//
		//
		//
		// Load_ShellshockParamsPtr_Hook.Create(0x821FB5D0, Load_ShellshockParamsPtr);
		//
		//
		Load_FogDefPtr_Hook.Create(0x82265E28, Load_FogDefPtr);
	}

	void Load()
	{
		Hooks();
	}

	void Unload()
	{
	}
}
