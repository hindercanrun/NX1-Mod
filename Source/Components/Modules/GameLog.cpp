#include "../../Util/FPS.h"

namespace GameLog
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Util::Hook::Detour Vehicle_ClearServerDefs_Hook;
		void Vehicle_ClearServerDefs()
		{
			Symbols::SP_Dev::Com_Printf(15, "------- Game Initialization -------\n");
			Symbols::SP_Dev::Com_Printf(15, "NX1-Mod\n");
			Symbols::SP_Dev::Com_Printf(15, "Time: %s\n", Util::String::GetCurrentTime());
			Symbols::SP_Dev::Com_Printf(15, "-----------------------------------\n");

			auto Invoke = Vehicle_ClearServerDefs_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void Hooks()
		{
			Vehicle_ClearServerDefs_Hook.Create(0x8256F0F8, Vehicle_ClearServerDefs);
		}

		void ClearHooks()
		{
			Vehicle_ClearServerDefs_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
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
		// TODO
#endif
	}
}
