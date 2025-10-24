namespace Assets
{
	void Dump_MapEnts(const MapEnts* mapEnts)
	{
#ifdef DUMP_ASSETS
		if (!mapEnts)
			return;

		std::string assetName = mapEnts->name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".ents";

		int len = mapEnts->numEntityChars;
		// skip null term
		if (mapEnts->entityString[len - 1] == '\0')
			--len;
		Util::FileSystem::WriteFileToDisk(outPath.c_str(), mapEnts->entityString, len);
#endif
	}
}
