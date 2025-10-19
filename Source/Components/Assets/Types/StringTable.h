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

	void DumpStringTables(const char* filename, StringTable** tablePtr, const char* a3);
}
