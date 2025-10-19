#pragma once

namespace Assets
{
	struct LocalizeEntry
	{
		const char* value;
		const char* name;
	};

	void Dump_LocalizeEntry(const LocalizeEntry* localizeEntry);
}
