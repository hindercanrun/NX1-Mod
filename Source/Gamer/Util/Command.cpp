#include "..\Std_Include.h"
#include "Command.h"

namespace Util
{
	namespace Command
	{
		static std::vector<Structs::cmd_function_s*> cmds;
		Structs::cmd_function_s* allocedCmd()
		{
			auto* cmd = new Structs::cmd_function_s;
			cmds.push_back(cmd);
			return cmd;
		}

		void Add(const char* cmdName, void(__cdecl* function)())
		{
			Symbols::Cmd_AddCommand(cmdName, function, allocedCmd());
		}
	}
}
