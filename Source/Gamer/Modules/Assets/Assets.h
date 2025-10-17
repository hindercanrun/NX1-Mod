#pragma once

// ASSET_TYPE_PHYSPRESET
// ASSET_TYPE_PHYSCOLLMAP - collmaps..? like .map? needs research
// ASSET_TYPE_XANIMPARTS
// ASSET_TYPE_XMODEL_SURFS - new, needs research
// ASSET_TYPE_XMODEL
// ASSET_TYPE_MATERIAL
// ASSET_TYPE_PIXELSHADER
// ASSET_TYPE_TECHNIQUE_SET
// ASSET_TYPE_IMAGE = 0x8,
// ASSET_TYPE_SOUND = 0x9,
// ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE - new, needs research
// ASSET_TYPE_SND_LPF_CURVE - new, needs research
// ASSET_TYPE_LOADED_SOUND - new, needs research
// ASSET_TYPE_CLIPMAP_SP
// ASSET_TYPE_CLIPMAP_MP - used to be CLIPMAP_PVS, anything else change?
// ASSET_TYPE_COMWORLD
// ASSET_TYPE_GAMEWORLD_SP
// ASSET_TYPE_GAMEWORLD_MP
// ASSET_TYPE_MAP_ENTS
// ASSET_TYPE_FXWORLD - new, needs research
// ASSET_TYPE_GFXWORLD
#include "Types\GfxLightDef.h"
// ASSET_TYPE_UI_MAP - never used
// ASSET_TYPE_FONT
// ASSET_TYPE_MENULIST
// ASSET_TYPE_MENU
#include "Types\LocalizeEntry.h"
// ASSET_TYPE_WEAPON
// ASSET_TYPE_SNDDRIVER_GLOBALS
// ASSET_TYPE_FX
// ASSET_TYPE_IMPACT_FX
// ASSET_TYPE_SURFACE_FX - new, needs research
// ASSET_TYPE_AITYPE - raw file
// ASSET_TYPE_MPTYPE - raw file
// ASSET_TYPE_CHARACTER - raw file
// ASSET_TYPE_XMODELALIAS - raw file
#include "Types\RawFile.h"
#include "Types\StringTable.h"
// ASSET_TYPE_LEADERBOARD - might be 1:1 to T6s
// ASSET_TYPE_STRUCTURED_DATA_DEF
// ASSET_TYPE_TRACER
// ASSET_TYPE_LASER - new, needs research
// ASSET_TYPE_VEHICLE
// ASSET_TYPE_ADDON_MAP_ENTS - possibly (?) never used
#include "Types\ShellShock.h"
// ASSET_TYPE_VOLUMESETTING - new, needs research
// ASSET_TYPE_REVERBPRESET - new, needs research
#include "Types\Fog.h"

namespace Assets
{
	void Load();
	void Unload();
}
