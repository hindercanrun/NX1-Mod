#pragma once

namespace Assets
{
	struct Bounds
	{
		float midPoint[3];
		float halfSize[3];
	};

	struct TriggerModel
	{
		int contents;
		unsigned short hullCount;
		unsigned short firstHull;
	};

	struct TriggerHull
	{
		Bounds bounds;
		int contents;
		unsigned short slabCount;
		unsigned short firstSlab;
	};

	struct TriggerSlab
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct MapTriggers
	{
		unsigned int count;
		TriggerModel* models;
		unsigned int hullCount;
		TriggerHull* hulls;
		unsigned int slabCount;
		TriggerSlab* slabs;
	};

	struct Stage
	{
		const char* name;
		float origin[3];
		unsigned short triggerIndex;
		unsigned char sunPrimaryLightIndex;
	};

	struct MapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		MapTriggers trigger;
		Stage* stages;
		unsigned char stageCount;
	};

	void Dump_MapEnts(const MapEnts* mapEnts);
}
