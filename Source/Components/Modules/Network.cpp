namespace Network
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Util::Hook::Detour sendto_Hook;
		int sendto_stub(SOCKET s, const char* buf, int len, int flags, sockaddr* to, int tolen)
		{
			if (tolen >= sizeof(sockaddr_in))
			{
				sockaddr_in* addr = (sockaddr_in*)to;
				unsigned char* ip = (unsigned char*)&addr->sin_addr.s_addr;
				Symbols::SP_Dev::Com_Printf(16, "sendto: sent %d bytes to %u.%u.%u.%u:%u\n", len, ip[0], ip[1], ip[2], ip[3], ntohs(addr->sin_port));
			}
			return len;
		}


		Util::Hook::Detour Live_IsUserSignedInToLive_Hook;
		bool Live_IsUserSignedInToLive(int controllerIndex)
		{
			return true;
		}

		Util::Hook::Detour LSP_Connected_Hook;
		int LSP_Connected()
		{
			return true;
		}

		Util::Hook::Detour dwGetLogOnStatus_Hook;
		Structs::DWOnlineStatus dwGetLogOnStatus()
		{
			*Symbols::SP_Dev::g_LogOnStatus = Structs::DW_NO_ACCOUNT_SIGNED_IN;
			return Structs::DW_LIVE_CONNECTING;
		}

		void Hooks()
		{
			sendto_Hook.Create(0x8266A010, sendto_stub);

			Live_IsUserSignedInToLive_Hook.Create(0x8251FDB0, Live_IsUserSignedInToLive);
			LSP_Connected_Hook.Create(0x825A15A8, LSP_Connected);

			dwGetLogOnStatus_Hook.Create(0x825CD1F8, dwGetLogOnStatus);
		}

		void ClearHooks()
		{
			Live_IsUserSignedInToLive_Hook.Clear();
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
