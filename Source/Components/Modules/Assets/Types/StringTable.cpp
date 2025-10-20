namespace Assets
{
	void Dump_StringTable(const StringTable* stringTable)
	{
#ifdef DUMP_ASSETS
		if (!stringTable)
			return;

		std::string assetName = stringTable->name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

		std::string csvTable;
		for (int i = 0; i < stringTable->rowCount; i++)
		{
			for (int j = 0; j < stringTable->columnCount; j++)
			{
				csvTable += stringTable->values[i * stringTable->columnCount + j].string;
				if (j < stringTable->columnCount - 1)
					csvTable += ",";
			}

			csvTable += "\n";
		}

		Util::FileSystem::WriteFileToDisk(outPath.c_str(), csvTable.c_str(), csvTable.size());
#endif
	}
}
