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

		// TODO: add to MP_DEMO
#ifdef SP_DEV	
		Args::Args() : nesting_(Symbols::SP_Dev::cmd_args->nesting)
		{
			this->nesting_ = Symbols::SP_Dev::cmd_args->nesting - 1;

			if (this->nesting_ < 0)
				this->nesting_ = 0;
		}

		int Args::Size() const
		{
			return Symbols::SP_Dev::cmd_args->argc[this->nesting_];
		}

		const char* Args::Get(const int index) const
		{
			if (index >= this->Size())
				return "";
			return Symbols::SP_Dev::cmd_args->argv[this->nesting_][index];
		}
#endif

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
