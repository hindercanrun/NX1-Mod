namespace Intro
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Util::Hook::Detour COM_PlayIntroMovies_Hook;
		void COM_PlayIntroMovies()
		{
			Symbols::SP_Dev::Cbuf_AddText(0, "autocinematic title\n");
		}

		void Hooks()
		{
			// play our own intro movie
			COM_PlayIntroMovies_Hook.Create(0x82428EF0, COM_PlayIntroMovies);
		}

		void ClearHooks()
		{
			COM_PlayIntroMovies_Hook.Clear();
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
		void PlayIntroMovie()
		{
			Symbols::MP_Demo::Cbuf_AddText(0, "autocinematic title\n");
		}

		Util::Hook::Detour Com_Init_Try_Block_Function_Hook;
		void Com_Init_Try_Block_Function(const char* p_command_line)
		{
			auto Invoke = Com_Init_Try_Block_Function_Hook.Invoke<void(*)(const char*)>();
			Invoke(p_command_line);

			PlayIntroMovie();
		}

		void Hooks()
		{
			// add a nice intro movie for when the game starts
			Com_Init_Try_Block_Function_Hook.Create(0x822DC5A8, Com_Init_Try_Block_Function);
		}

		void ClearHooks()
		{
			Com_Init_Try_Block_Function_Hook.Clear();
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
}
