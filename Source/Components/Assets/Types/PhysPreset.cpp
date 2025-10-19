#include "PhysPreset.h"

namespace Assets
{
	void Dump_PhysPreset(const PhysPreset* physPreset)
	{
		if (!physPreset)
			return;

		std::string assetName = physPreset->name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\physic\\" + assetName;
		std::ostringstream oss;

		oss << "PHYSIC"
			<< "\\sndAliasPrefix\\" << physPreset->sndAliasPrefix
			<< "\\mass\\" << physPreset->mass
			<< "\\friction\\" << physPreset->friction
			<< "\\isFrictionInfinity\\0" // always 0
			<< "\\bounce\\" << physPreset->bounce
			<< "\\bulletForceScale\\" << physPreset->bulletForceScale
			<< "\\explosiveForceScale\\" << physPreset->explosiveForceScale
			<< "\\piecesSpreadFraction\\" << physPreset->piecesSpreadFraction
			<< "\\piecesUpwardVelocity\\" << physPreset->piecesUpwardVelocity
			<< "\\tempDefaultToCylinder\\" << ((physPreset->tempDefaultToCylinder) ? 1 : 0)
			<< "\\perSurfaceSndAlias\\" << ((physPreset->perSurfaceSndAlias) ? 1 : 0)
			<< "\n";

		oss << "SND_PARAMS"
			<< "\\soundPitchLow\\" << physPreset->sndParams.soundPitchLow
			<< "\\soundPitchHigh\\" << physPreset->sndParams.soundPitchHigh
			<< "\\soundVolLow\\" << physPreset->sndParams.soundVolLow
			<< "\\soundVolHigh\\" << physPreset->sndParams.soundVolHigh
			<< "\\soundImpactRangeLow\\" << physPreset->sndParams.soundImpactRangeLow
			<< "\\soundImpactRangeHigh\\" << physPreset->sndParams.soundImpactRangeHigh
			<< "\n";

		std::string data = oss.str();
		Util::FileSystem::WriteFileToDisk(outPath.c_str(), data.c_str(), data.size());
	}
}
