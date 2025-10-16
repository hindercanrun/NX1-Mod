namespace Util
{
	namespace Print
	{
		static FILE* g_consoleLog = NULL;

		void OpenLogFile()
		{
			if (g_consoleLog)
				return;

			g_consoleLog = fopen("game:/" BASE_FOLDER "/logs/console.log", "w");
			if (!g_consoleLog)
				return;

			time_t now = time(NULL);
			struct tm* t = localtime(&now);
			if (t)
			{
				fprintf(g_consoleLog, "Logfile opened on %s\n", asctime(t));
			}

			fflush(g_consoleLog);
		}

		void LogPrintMessage(const char* msg)
		{
			if (!g_consoleLog)
				OpenLogFile();

			if (g_consoleLog)
			{
				fprintf(g_consoleLog, "%s", msg);
				fflush(g_consoleLog);
			}
		}

		const char* Printf(const char* fmt, ...)
		{
			static char buf[32000];

			va_list args;
			va_start(args, fmt);
			vsprintf_s(buf, sizeof(buf), fmt, args);
			va_end(args);

			const char* msg = buf;

			Symbols::CL_ConsolePrint(0, 0, msg, 0, 0, 0);

			LogPrintMessage(msg);
			return buf;
		}
	}
}
