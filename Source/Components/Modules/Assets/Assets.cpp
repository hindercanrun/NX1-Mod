#include "Assets.h"

namespace Assets
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Util::Hook::Detour Load_PhysPresetPtr_Hook;
		void Load_PhysPresetPtr(bool atStreamStart)
		{
			auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			PhysPreset** varPhysPresetPtr = *(PhysPreset***)0x82C6E7E0;
			if (varPhysPresetPtr && *varPhysPresetPtr)
			{
#ifdef DUMP_ASSETS
				Dump_PhysPreset(*varPhysPresetPtr);
#elif LOAD_ASSETS
				Load_PhysPreset(*varPhysPresetPtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_MapEnts(*varMapEntsPtr);
#elif LOAD_ASSETS
				Load_MapEnts(*varMapEntsPtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_LocalizeEntry(*varLocalizeEntryPtr);
#elif LOAD_ASSETS
				Load_LocalizeEntry(*varLocalizeEntryPtr);
#endif
			}
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

			StringTable** varStringTablePtr = *(StringTable***)0x82C6DF5C;
			if (varStringTablePtr && *varStringTablePtr)
			{
#ifdef DUMP_ASSETS
				Dump_StringTable(*varStringTablePtr);
#elif LOAD_ASSETS
				Load_StringTable(*varStringTablePtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_TracerDef(*varTracerDefPtr);
#elif LOAD_ASSETS
				Load_TracerDef(*varTracerDefPtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_ShellshockParams(*varShellshockParamsPtr);
#elif LOAD_ASSETS
				Load_ShellshockParams(*varShellshockParamsPtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_FogDef(*varFogDefPtr);
#elif LOAD_ASSETS
				Load_FogDef(*varFogDefPtr);
#endif
			}
		}

		void Hooks()
		{
			Load_PhysPresetPtr_Hook.Create(0x82250C00, Load_PhysPresetPtr);
			// ASSET_TYPE_PHYSCOLLMAP
			// ASSET_TYPE_XANIMPARTS
			// ASSET_TYPE_XMODEL_SURFS
			// ASSET_TYPE_XMODEL
			// ASSET_TYPE_MATERIAL
			// ASSET_TYPE_PIXELSHADER
			// ASSET_TYPE_TECHNIQUE_SET
			// ASSET_TYPE_IMAGE = 0x8,
			// ASSET_TYPE_SOUND = 0x9,
			// ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE
			// ASSET_TYPE_SND_LPF_CURVE
			// ASSET_TYPE_LOADED_SOUND
			// ASSET_TYPE_CLIPMAP_SP
			// ASSET_TYPE_CLIPMAP_MP
			// ASSET_TYPE_COMWORLD
			// ASSET_TYPE_GAMEWORLD_SP
			// ASSET_TYPE_GAMEWORLD_MP
			Load_MapEntsPtr_Hook.Create(0x82259EF0, Load_MapEntsPtr);
			// ASSET_TYPE_FXWORLD
			// ASSET_TYPE_GFXWORLD
			// ASSET_TYPE_LIGHT_DEF
			// ASSET_TYPE_UI_MAP
			// ASSET_TYPE_FONT
			// ASSET_TYPE_MENULIST
			// ASSET_TYPE_MENU
			Load_LocalizeEntryPtr_Hook.Create(0x8225FD28, Load_LocalizeEntryPtr);
			// ASSET_TYPE_WEAPON
			// ASSET_TYPE_SNDDRIVER_GLOBALS
			// ASSET_TYPE_FX
			// ASSET_TYPE_IMPACT_FX
			// ASSET_TYPE_SURFACE_FX
			// ASSET_TYPE_AITYPE
			// ASSET_TYPE_MPTYPE
			// ASSET_TYPE_CHARACTER
			// ASSET_TYPE_XMODELALIAS
			DB_GetRawBuffer_Hook.Create(0x82288630, DB_GetRawBuffer);
			Load_StringTablePtr_Hook.Create(0x82263550, Load_StringTablePtr);
			// ASSET_TYPE_LEADERBOARD
			// ASSET_TYPE_STRUCTURED_DATA_DEF
			Load_TracerDefPtr_Hook.Create(0x822603F0, Load_TracerDefPtr);
			// ASSET_TYPE_LASER
			// ASSET_TYPE_VEHICLE
			// ASSET_TYPE_ADDON_MAP_ENTS
			Load_ShellshockParamsPtr_Hook.Create(0x8226C5C0, Load_ShellshockParamsPtr);
			// ASSET_TYPE_VOLUMESETTING
			// ASSET_TYPE_REVERBPRESET
			Load_FogDefPtr_Hook.Create(0x82265E28, Load_FogDefPtr);
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
		}
#endif
	}

	namespace MP_Dev
	{
#ifdef MP_DEV
		// TODO
#endif
	}

	namespace SP_Demo
	{
#ifdef SP_DEMO
		// TODO
#endif
	}

	namespace MP_Demo
	{
#ifdef MP_DEMO
		Util::Hook::Detour Load_PhysPresetPtr_Hook;
		void Load_PhysPresetPtr(bool atStreamStart)
		{
			auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			PhysPreset** varPhysPresetPtr = *(PhysPreset***)0x828BE9E0;
			if (varPhysPresetPtr && *varPhysPresetPtr)
			{
#ifdef DUMP_ASSETS
				Dump_PhysPreset(*varPhysPresetPtr);
#elif LOAD_ASSETS
				Load_PhysPreset(*varPhysPresetPtr);
#endif
			}
		}

		Util::Hook::Detour Load_MapEntsPtr_Hook;
		void Load_MapEntsPtr(bool atStreamStart)
		{
			auto Invoke = Load_MapEntsPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			MapEnts** varMapEntsPtr = *(MapEnts***)0x828BE9F8;
			if (varMapEntsPtr && *varMapEntsPtr)
			{
#ifdef DUMP_ASSETS
				Dump_MapEnts(*varMapEntsPtr);
#elif LOAD_ASSETS
				Load_MapEnts(*varMapEntsPtr);
#endif
			}
		}

		Util::Hook::Detour Load_LocalizeEntryPtr_Hook;
		void Load_LocalizeEntryPtr(bool atStreamStart)
		{
			auto Invoke = Load_LocalizeEntryPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			LocalizeEntry** varLocalizeEntryPtr = *(LocalizeEntry***)0x828BEB5C;
			if (!varLocalizeEntryPtr || !*varLocalizeEntryPtr)
			{
#ifdef DUMP_ASSETS
				Dump_LocalizeEntry(*varLocalizeEntryPtr);
#elif LOAD_ASSETS
				Load_LocalizeEntry(*varLocalizeEntryPtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_StringTable(*varStringTablePtr);
#elif LOAD_ASSETS
				Load_StringTable(*varStringTablePtr);
#endif
			}
		}

		Util::Hook::Detour Load_TracerDefPtr_Hook;
		void Load_TracerDefPtr(bool atStreamStart)
		{
			auto Invoke = Load_TracerDefPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			TracerDef** varTracerDefPtr = *(TracerDef***)0x828BEA34;
			if (varTracerDefPtr && *varTracerDefPtr)
			{
#ifdef DUMP_ASSETS
				Dump_TracerDef(*varTracerDefPtr);
#elif LOAD_ASSETS
				Load_TracerDef(*varTracerDefPtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_ShellshockParams(*varShellshockParamsPtr);
#elif LOAD_ASSETS
				Load_ShellshockParams(*varShellshockParamsPtr);
#endif
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
#ifdef DUMP_ASSETS
				Dump_FogDef(*varFogDefPtr);
#elif LOAD_ASSETS
				Load_FogDef(*varFogDefPtr);
#endif
			}
		}

		void Hooks()
		{
			Load_PhysPresetPtr_Hook.Create(0x821E1F00, Load_PhysPresetPtr);
			// ASSET_TYPE_PHYSCOLLMAP
			// ASSET_TYPE_XANIMPARTS
			// ASSET_TYPE_XMODEL_SURFS
			// ASSET_TYPE_XMODEL
			// ASSET_TYPE_MATERIAL
			// ASSET_TYPE_PIXELSHADER
			// ASSET_TYPE_TECHNIQUE_SET
			// ASSET_TYPE_IMAGE = 0x8,
			// ASSET_TYPE_SOUND = 0x9,
			// ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE
			// ASSET_TYPE_SND_LPF_CURVE
			// ASSET_TYPE_LOADED_SOUND
			// ASSET_TYPE_CLIPMAP_SP
			// ASSET_TYPE_CLIPMAP_MP
			// ASSET_TYPE_COMWORLD
			// ASSET_TYPE_GAMEWORLD_SP
			// ASSET_TYPE_GAMEWORLD_MP
			Load_MapEntsPtr_Hook.Create(0x821EA608, Load_MapEntsPtr);
			// ASSET_TYPE_FXWORLD
			// ASSET_TYPE_GFXWORLD
			// ASSET_TYPE_LIGHT_DEF
			// ASSET_TYPE_UI_MAP
			// ASSET_TYPE_FONT
			// ASSET_TYPE_MENULIST
			// ASSET_TYPE_MENU
			Load_LocalizeEntryPtr_Hook.Create(0x821EFC90, Load_LocalizeEntryPtr);
			// ASSET_TYPE_WEAPON
			// ASSET_TYPE_SNDDRIVER_GLOBALS
			// ASSET_TYPE_FX
			// ASSET_TYPE_IMPACT_FX
			// ASSET_TYPE_SURFACE_FX
			// ASSET_TYPE_AITYPE
			// ASSET_TYPE_MPTYPE
			// ASSET_TYPE_CHARACTER
			// ASSET_TYPE_XMODELALIAS
			DB_GetRawBuffer_Hook.Create(0x822140E0, DB_GetRawBuffer);
			Load_StringTablePtr_Hook.Create(0x821F2F18, Load_StringTablePtr);
			// ASSET_TYPE_LEADERBOARD
			// ASSET_TYPE_STRUCTURED_DATA_DEF
			Load_TracerDefPtr_Hook.Create(0x821F0308, Load_TracerDefPtr);
			// ASSET_TYPE_LASER
			// ASSET_TYPE_VEHICLE
			// ASSET_TYPE_ADDON_MAP_ENTS
			Load_ShellshockParamsPtr_Hook.Create(0x821FB5D0, Load_ShellshockParamsPtr);
			// ASSET_TYPE_VOLUMESETTING
			// ASSET_TYPE_REVERBPRESET
			Load_FogDefPtr_Hook.Create(0x821F5488, Load_FogDefPtr);
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
		}
#endif
	}
}
