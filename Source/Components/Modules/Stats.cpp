#include "../../Util/FPS.h"

namespace Stats
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Util::Hook::Detour GamerProfile_GetPlayTimeSP_Hook;
		unsigned int GamerProfile_GetPlayTimeSP(int controllerIndex)
		{
			//auto g_gameMode = Symbols::SP_Dev::Dvar_FindVar("gameMode");
			//if (g_gameMode->current.integer == 1)
			//	return;

			int elapsed = (Symbols::SP_Dev::Sys_MillisecondsRaw() - Symbols::SP_Dev::g_playStartTime[controllerIndex]) / 1000;
			return elapsed;
		}

		Util::Hook::Detour GamerProfile_GetPlayTimeSO_Hook;
		unsigned int GamerProfile_GetPlayTimeSO(int controllerIndex)
		{
			//auto g_gameMode = Symbols::SP_Dev::Dvar_FindVar("gameMode");
			//if (g_gameMode->current.integer == 2)
			//	return;

			int elapsed = (Symbols::SP_Dev::Sys_MillisecondsRaw() - Symbols::SP_Dev::g_playStartTime[controllerIndex]) / 1000;
			return elapsed;
		}

		void Hooks()
		{
			GamerProfile_GetPlayTimeSP_Hook.Create(0x822284F8, GamerProfile_GetPlayTimeSP);
			GamerProfile_GetPlayTimeSO_Hook.Create(0x82228568, GamerProfile_GetPlayTimeSO);
		}

		void ClearHooks()
		{
			GamerProfile_GetPlayTimeSP_Hook.Clear();
			GamerProfile_GetPlayTimeSO_Hook.Clear();
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
