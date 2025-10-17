namespace Assets
{
	void DumpStringTables(const char* filename, StringTable** tablePtr, const char* a3)
	{
		// Validate result
		if (!tablePtr || !*tablePtr)
			return;

		StringTable* table = *tablePtr;
		if (!table || !table->values)
			return;

		// Prepare dump path
		char path[256];
		_snprintf(path, sizeof(path), "game:/nx1-data/dump/%s", filename);
		path[sizeof(path) - 1] = '\0';

		FILE* f = fopen(path, "wb");
		if (!f)
		{
			Util::Print::Printf("Failed to open dump path: %s\n", path);
			return;
		}

		// Dump contents
		int totalCells = table->columnCount * table->rowCount;
		for (int row = 0; row < table->rowCount; ++row)
		{
			for (int col = 0; col < table->columnCount; ++col)
			{
				int index = row * table->columnCount + col;
				const char* str = nullptr;

				if (index >= 0 && index < totalCells)
					str = table->values[index].string;

				if (str)
				{
					// Escape commas/quotes for CSV
					bool hasComma = strchr(str, ',') != nullptr;
					bool hasQuote = strchr(str, '"') != nullptr;
					if (hasComma || hasQuote)
					{
						fputc('"', f);
						for (const char* p = str; *p; ++p)
						{
							if (*p == '"') fputc('"', f); // double quotes inside CSV
							fputc(*p, f);
						}
						fputc('"', f);
					}
					else
					{
						fputs(str, f);
					}
				}

				if (col < table->columnCount - 1)
					fputc(',', f);
			}

			fputc('\n', f);
		}

		Util::Print::Printf("dumped stringtable '%s'\n", filename);

		fclose(f);
	}
}
