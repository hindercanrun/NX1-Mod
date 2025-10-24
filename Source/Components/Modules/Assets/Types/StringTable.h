#pragma once

namespace Assets
{
	struct StringTableCell
	{
		const char* string;
		int hash;
	};

	struct StringTable
	{
		const char* name;
		int columnCount;
		int rowCount;
		StringTableCell* values;
	};

	void Dump_StringTable(const StringTable* stringTable);
}
