#include "MapEnts.h"

namespace Assets
{
	void Dump_MapEnts(const MapEnts* mapEnts)
	{
		if (!mapEnts)
			return;

		std::string assetName = mapEnts->name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".ents";

		int lengthToWrite = mapEnts->numEntityChars;
		if (mapEnts->entityString[lengthToWrite - 1] == '\0')
			--lengthToWrite;
		Util::FileSystem::WriteFileToDisk(outPath.c_str(), mapEnts->entityString, lengthToWrite);
	}
}
