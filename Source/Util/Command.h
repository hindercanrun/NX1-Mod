#pragma once

namespace Util
{
	namespace Command
	{
		class Args
		{
		public:
			Args();

			int Size() const;
			const char* Get(int index) const;

		private:
			int nesting_;
		};

		void Add(const char* cmdName, void(__cdecl* function)());
	}
}
