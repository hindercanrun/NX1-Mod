#pragma once

namespace Util
{
	namespace Command
	{
#ifdef SP_DEV
		class Args
		{
		public:
			Args();

			int Size() const;
			const char* Get(int index) const;

			const char* operator[](const int index) const { return this->Get(index); }
		private:
			int nesting_;
		};
#endif

		void Add(const char* cmdName, void(__cdecl* function)());
	}
}
