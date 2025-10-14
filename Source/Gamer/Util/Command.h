#pragma once

namespace Util
{
	namespace Command
	{
		void Add(const char* cmdName, void(__cdecl* function)());
	}
}
