#include "LocalizeEntry.h"

namespace Assets
{
	const char* LocalizedStrings_GetFileNotes(const std::string& prefix)
	{
		if (prefix == "debug")
			return "Strings used for debugging go in this file.";
		else if (prefix == "game")
			return "Game messages made by the server game dll go in this file.";
		else if (prefix == "menu")
			return "Strings displayed in the menus go in this file.";
		else if (prefix == "script")
			return "All game messages made by script should go in this file.";
		else if (prefix == "weapon")
			return "Strings used in the weapon settings go in this file.";
		return ""; // no known strings
	}

	void Dump_LocalizeEntry(const LocalizeEntry* localizeEntry)
	{
		if (!localizeEntry)
			return;

		std::string assetName = localizeEntry->name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\english\\localizedstrings\\" + assetName + ".str";

		Util::FileSystem::WriteFileToDisk(outPath.c_str(), "2", 2);
	}
}
