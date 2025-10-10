#include "../Std_Include.h"
#include "String.h"

namespace Util
{
	namespace String
	{
		const char* va(const char* fmt, ...)
		{
			static char buf[32000];

			va_list args;
			va_start(args, fmt);
			vsprintf_s(buf, sizeof(buf), fmt, args);
			va_end(args);

			return buf;
		}
	}
}
