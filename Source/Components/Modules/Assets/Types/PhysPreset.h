#pragma once

namespace Assets
{
	struct sndPhysicsParams
	{
		float soundPitchLow;
		float soundPitchHigh;
		float soundVolLow;
		float soundVolHigh;
		float soundImpactRangeLow;
		float soundImpactRangeHigh;
	};

	struct PhysPreset
	{
		const char* name;
		int type;
		float mass;
		float bounce;
		float friction;
		float bulletForceScale;
		float explosiveForceScale;
		const char* sndAliasPrefix;
		sndPhysicsParams sndParams;
		float piecesSpreadFraction;
		float piecesUpwardVelocity;
		bool tempDefaultToCylinder;
		bool perSurfaceSndAlias;
	};

	void Dump_PhysPreset(const PhysPreset* physPreset);
}
