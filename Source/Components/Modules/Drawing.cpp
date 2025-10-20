#include "../../Util/FPS.h"

namespace Drawing
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Structs::Font_s** Font;

		Util::Hook::Detour DevGui_GetScreenXPad_Hook;
		int DevGui_GetScreenXPad()
		{
			return 0;
		}

		Util::Hook::Detour DevGui_GetScreenYPad_Hook;
		int DevGui_GetScreenYPad()
		{
			return 0;
		}

		void DrawWatermark()
		{
			if (!*Font)
				return;

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::SP_Dev::R_AddCmdDrawText("NX1-Mod", MAX_CHARS, *Font, 2.0f, 20.0f, 0.8f, 0.8f, 0.0f, colour, 3, Structs::SL_SYSTEM);
		}

		Util::FpsCounter g_fps;

		void DrawFPS()
		{
			if (!*Font)
				return;

			g_fps.Update();

			float colourGood[4] = { 0.6f, 1.0f, 0.0f, 1.0f };
			float colourOkay[4] = { 1.0f, 0.7f, 0.3f, 1.0f };
			float colourBad[4]  = { 1.0f, 0.3f, 0.3f, 1.0f };

			float fpsValue = g_fps.GetFPS();
			int fpsInt = (int)fpsValue + 0.5f;

			float* textColour = (fpsInt >= 60)
				? colourGood
				: (fpsInt >= 50)
				? colourOkay
				: colourBad;

			std::stringstream ss;
			ss << fpsInt;
			std::string text = ss.str();

			if (fpsInt <= 99)
				Symbols::SP_Dev::R_AddCmdDrawText(text.c_str(), MAX_CHARS, *Font, 1255.0f, 20.0f, 1.0f, 1.0f, 0.0f, textColour, 3, Structs::SL_SYSTEM);
			else
				Symbols::SP_Dev::R_AddCmdDrawText(text.c_str(), MAX_CHARS, *Font, 1245.0f, 20.0f, 1.0f, 1.0f, 0.0f, textColour, 3, Structs::SL_SYSTEM);
		}

		Util::Hook::Detour CL_DrawScreen_Hook;
		void CL_DrawScreen()
		{
			DrawWatermark();
			DrawFPS();

			auto Invoke = CL_DrawScreen_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void Hooks()
		{
			Font = (Structs::Font_s**)0x8423B21C; // fonts/smallfont

			// Match the Dev Gui safe area on PC!
			DevGui_GetScreenXPad_Hook.Create(0x8229D748, DevGui_GetScreenXPad);
			DevGui_GetScreenYPad_Hook.Create(0x8229D7B0, DevGui_GetScreenYPad);

			CL_DrawScreen_Hook.Create(0x8221F858, CL_DrawScreen);

			// Disable some drawing
			Util::Hook::SetValue(0x8221F894, 0x60000000); // CG_DrawVersion
			Util::Hook::SetValue(0x824A6F3C, 0x60000000); // UI_DrawBuildNumber
		}

		void ClearHooks()
		{
			CL_DrawScreen_Hook.Clear();
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
