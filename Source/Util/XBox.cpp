namespace Util
{
	namespace XBox
	{
		const char* GetFakeThreadName(uint32_t threadId)
		{
			switch (threadId % 8)
			{
			case 0:
				return "MainThread";
			case 1:
				return "RenderThread";
			case 2:
				return "WorkerThread0";
			case 3:
				return "WorkerThread1";
			case 4:
				return "AudioThread";
			case 5:
				return "NetworkThread";
			case 6:
				return "StreamThread";
			case 7:
				return "CommsThread";
			default:
				return "UnknownThread";
			}
		}

		int DmGetThreadInfoEx(uint32_t threadId, DM_THREADINFOEX* info)
		{
			if (!info)
				return -1;

			std::memset(info, 0, sizeof(DM_THREADINFOEX));
			info->Size = sizeof(DM_THREADINFOEX);
			info->CurrentProcessor = threadId % 6;
			info->ThreadNameAddress = const_cast<char*>(GetFakeThreadName(threadId));

			info->Priority = 8 + (threadId % 3);
			info->SuspendCount = 0;
			info->StartAddress = 0x82000000 + (threadId * 0x1000);
			info->StackBase = 0x85000000;
			info->StackLimit = 0x84FF0000;
			return S_OK;
		}
	}
}
