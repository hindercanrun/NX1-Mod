#pragma once

namespace Util
{
	namespace XBox
	{
		struct DM_THREADINFOEX
		{
			uint32_t Size;
			uint32_t SuspendCount;
			uint32_t Priority;
			uint32_t LastError;
			uint32_t TlsBase;
			uint32_t StartAddress;
			uint32_t StackBase;
			uint32_t StackLimit;
			uint32_t KernelTime;
			uint32_t UserTime;
			uint32_t CreateTime;
			uint32_t CurrentProcessor;
			char* ThreadNameAddress;
		};

		int DmGetThreadInfoEx(uint32_t threadId, DM_THREADINFOEX* info);
	}
}
