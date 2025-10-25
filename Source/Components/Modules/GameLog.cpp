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

		static FILE* logfile = NULL;

		void Com_OpenLogFile()
		{
			if (logfile)
				return;

			logfile = fopen("game:/" BASE_FOLDER "/logs/console.log", "w");
			if (!logfile)
				return;

			time_t now = time(NULL);
			struct tm* t = localtime(&now);
			if (t)
			{
				Symbols::SP_Dev::Com_Printf(16, "Logfile opened on %s\n", asctime(t));
			}

			fflush(logfile);
		}

		void Com_LogPrintMessage(const char* msg)
		{
			if (!logfile)
				Com_OpenLogFile();

			if (logfile)
			{
				fprintf(logfile, msg);
				fflush(logfile);
			}
		}

		Util::Hook::Detour Com_PrintMessage_Hook;
		void Com_PrintMessage(int channel, const char* fmt, int error)
		{
			if (fmt && *fmt == '^' && fmt[1])
				fmt += 2;

			if (channel != 6)
			{
				Symbols::SP_Dev::CL_ConsolePrint(0, 0, fmt, 0, 0, 0);
			}

			if (channel != 7/* && com_logfile->current.integer*/)
			{
				Com_LogPrintMessage(fmt);
			}
		}

		Util::Hook::Detour Com_Printf_Hook;
		void Com_Printf(int channel, const char *fmt, ...)
		{
			char buffer[4096];

			va_list args;
			va_start(args, fmt);
			vsnprintf(buffer, sizeof(buffer), fmt, args);
			va_end(args);

			buffer[sizeof(buffer) - 1] = '\0';

			Com_PrintMessage(channel, buffer, 0);
		}

		Util::Hook::Detour Com_PrintWarning_Hook;
		void Com_PrintWarning(int channel, const char* fmt, ...)
		{
			char formatted[4096];
			char buffer[4096];

			va_list args;
			va_start(args, fmt);
			vsnprintf(formatted, sizeof(formatted), fmt, args);
			va_end(args);

			formatted[sizeof(formatted) - 1] = '\0';

			_snprintf(buffer, sizeof(buffer), "^3Warning: %s", formatted);
			buffer[sizeof(buffer) - 1] = '\0';

			Com_PrintMessage(channel, buffer, 2);
		}

		Util::Hook::Detour Com_PrintError_Hook;
		void Com_PrintError(int channel, const char* fmt, ...)
		{
			char formatted[4096];
			char buffer[4096];

			va_list args;
			va_start(args, fmt);
			vsnprintf(formatted, sizeof(formatted), fmt, args);
			va_end(args);

			formatted[sizeof(formatted) - 1] = '\0';

			_snprintf(buffer, sizeof(buffer), "^1Error: %s", formatted);
			buffer[sizeof(buffer) - 1] = '\0';

			Com_PrintMessage(channel, buffer, 3);
		}

		void Hooks()
		{
			Vehicle_ClearServerDefs_Hook.Create(0x8256F0F8, Vehicle_ClearServerDefs);

			Com_Printf_Hook.Create(0x82427A50, Com_Printf);
			Com_PrintWarning_Hook.Create(0x8242BB70, Com_PrintWarning);
			Com_PrintError_Hook.Create(0x8242B930, Com_PrintError);

			Util::Hook::SetString(0x820630E4, "Pathnode %d (%s) at %s %s.\n");
			Util::Hook::SetString(0x82044370, "^3Spawner [%d] at (%g %g %g) is in solid\n");
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
