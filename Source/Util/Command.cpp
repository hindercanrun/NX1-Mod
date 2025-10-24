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

		// INFO: modify this when other versions get full custom command support
		static Structs::CmdArgs*& g_cmd_args = Symbols::SP_Dev::cmd_args;

		Args::Args()
		{
			this->nesting_ = g_cmd_args->nesting - 1;

			if (this->nesting_ < 0)
				this->nesting_ = 0;
		}

		int Args::Size() const
		{
			return g_cmd_args->argc[nesting_];
		}

		const char* Args::Get(int index) const
		{
			if (index >= g_cmd_args->argc[this->nesting_])
				return "";
			return g_cmd_args->argv[this->nesting_][index];
		}

		void Add(const char* cmdName, void(__cdecl* function)())
		{
#ifdef SP_DEV
			Symbols::SP_Dev::Cmd_AddCommand(cmdName, function, allocedCmd());
#elif MP_DEMO
			Symbols::MP_Demo::Cmd_AddCommand(cmdName, function, allocedCmd());
#endif
		}
	}
}
