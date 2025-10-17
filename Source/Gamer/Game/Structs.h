#pragma once

namespace Structs
{
	struct cmd_function_s
	{
		cmd_function_s* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void (__cdecl* function)();
	};

	enum DvarSetSource
	{
		DVAR_SOURCE_INTERNAL,
		DVAR_SOURCE_EXTERNAL,
		DVAR_SOURCE_SCRIPT,
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		unsigned char color[4];
	};

	struct EnumLimit
	{
		int stringCount;
		const char** strings;
	};

	struct IntLimit
	{
		int min;
		int max;
	};

	struct FloatLimit
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		EnumLimit enumeration;
		IntLimit integer;
		FloatLimit value;
		FloatLimit vector;
	};

	struct dvar_t
	{
		const char* name;
		const char* description;
		unsigned int flags;
		char type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		dvar_t* hashNext;
	};

	struct SysFile
	{
		HANDLE handle;
		int startOffset;
	};

	struct DBFile
	{
		SysFile handle;
		char name[64];
	};

	struct db_internal_state
	{
		int dummy;
	};

	typedef struct
	{
		Bytef* next_in; /* next input byte */
		uInt avail_in;  /* number of bytes available at next_in */
		uInt total_in;  /* total number of input bytes read so far */

		unsigned __int8* next_out; /* next output byte will go here */
		uInt avail_out; /* remaining free space at next_out */
		uInt total_out; /* total number of bytes output so far */

		char* msg; /* last error message, NULL if no error */

		db_internal_state* state; /* not visible by applications */

		alloc_func zalloc;  /* used to allocate the internal state */
		free_func  zfree;   /* used to free the internal state */
		voidpf opaque; /* private data object passed to zalloc and zfree */

		int data_type; /* best guess about the data type: binary or text for deflate, or the decoding state for inflate */
	} db_z_stream_s;

	struct DBLoadData
	{
		DBFile* p_file;
		int outstandingRead;

		Bytef* p_fileBuffer;
		uInt readSize;
		uInt completedReadSize;
		uInt offset;

		Bytef* p_startIn;

		OVERLAPPED overlapped;

		uInt readError;

		db_z_stream_s stream;

		uInt lookaheadReadSize;
		uInt lookaheadOffset;
		uInt lookaheadClearAvailIn;
	};

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};

enum XAssetType : __int32
{
  ASSET_TYPE_PHYSPRESET = 0x0,
  ASSET_TYPE_PHYSCOLLMAP = 0x1,
  ASSET_TYPE_XANIMPARTS = 0x2,
  ASSET_TYPE_XMODEL_SURFS = 0x3,
  ASSET_TYPE_XMODEL = 0x4,
  ASSET_TYPE_MATERIAL = 0x5,
  ASSET_TYPE_PIXELSHADER = 0x6,
  ASSET_TYPE_TECHNIQUE_SET = 0x7,
  ASSET_TYPE_IMAGE = 0x8,
  ASSET_TYPE_SOUND = 0x9,
  ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE = 0xA,
  ASSET_TYPE_SND_LPF_CURVE = 0xB,
  ASSET_TYPE_LOADED_SOUND = 0xC,
  ASSET_TYPE_CLIPMAP_SP = 0xD,
  ASSET_TYPE_CLIPMAP_MP = 0xE,
  ASSET_TYPE_COMWORLD = 0xF,
  ASSET_TYPE_GAMEWORLD_SP = 0x10,
  ASSET_TYPE_GAMEWORLD_MP = 0x11,
  ASSET_TYPE_MAP_ENTS = 0x12,
  ASSET_TYPE_FXWORLD = 0x13,
  ASSET_TYPE_GFXWORLD = 0x14,
  ASSET_TYPE_LIGHT_DEF = 0x15,
  ASSET_TYPE_UI_MAP = 0x16,
  ASSET_TYPE_FONT = 0x17,
  ASSET_TYPE_MENULIST = 0x18,
  ASSET_TYPE_MENU = 0x19,
  ASSET_TYPE_LOCALIZE_ENTRY = 0x1A,
  ASSET_TYPE_WEAPON = 0x1B,
  ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1C,
  ASSET_TYPE_FX = 0x1D,
  ASSET_TYPE_IMPACT_FX = 0x1E,
  ASSET_TYPE_SURFACE_FX = 0x1F,
  ASSET_TYPE_AITYPE = 0x20,
  ASSET_TYPE_MPTYPE = 0x21,
  ASSET_TYPE_CHARACTER = 0x22,
  ASSET_TYPE_XMODELALIAS = 0x23,
  ASSET_TYPE_RAWFILE = 0x24,
  ASSET_TYPE_STRINGTABLE = 0x25,
  ASSET_TYPE_LEADERBOARD = 0x26,
  ASSET_TYPE_STRUCTURED_DATA_DEF = 0x27,
  ASSET_TYPE_TRACER = 0x28,
  ASSET_TYPE_LASER = 0x29,
  ASSET_TYPE_VEHICLE = 0x2A,
  ASSET_TYPE_ADDON_MAP_ENTS = 0x2B,
  ASSET_TYPE_SHOCKFILE = 0x2C,
  ASSET_TYPE_VOLUMESETTING = 0x2D,
  ASSET_TYPE_REVERBPRESET = 0x2E,
  ASSET_TYPE_FOG = 0x2F,
  ASSET_TYPE_COUNT = 0x30,
  ASSET_TYPE_STRING = 0x30,
  ASSET_TYPE_ASSETLIST = 0x31,
};

struct LocalizeEntry
{
  const char *value;
  const char *name;
};

union XAssetHeader
{/*
  PhysPreset *physPreset;
  PhysCollmap *physCollmap;
  XAnimParts *parts;
  XModelSurfs *modelSurfs;
  XModel *model;
  Material *material;
  MaterialPixelShader *pixelShader;
  MaterialVertexShader *vertexShader;
  MaterialVertexDeclaration *vertexDecl;
  MaterialTechniqueSet *techniqueSet;
  GfxImage *image;
  SndAliasList *sound;
  SndVfCurve *sndVfCurve;
  SndLpfCurve *sndLpfCurve;
  LoadedSound *loadSnd;
  clipMap_t *clipMap;
  ComWorld *comWorld;
  GameWorldSp *gameWorldSp;
  GameWorldMp *gameWorldMp;
  MapEnts *mapEnts;
  FxWorld *fxWorld;
  GfxWorld *gfxWorld;
  GfxLightDef *lightDef;
  Font_s *font;
  MenuList *menuList;
  menuDef_t *menu;*/
  LocalizeEntry *localize;
  /*WeaponCompleteDef *weapon;
  SndDriverGlobals *sndDriverGlobals;
  const FxEffectDef *fx;
  FxImpactTable *impactFx;
  SurfaceFxTable *surfaceFx;
  RawFile *rawfile;
  StringTable *stringTable;
  LeaderboardDef *leaderboardDef;
  StructuredDataDefSet *structuredDataDefSet;
  TracerDef *tracerDef;
  LaserDef *laserDef;
  VehicleDef *vehDef;
  AddonMapEnts *addonMapEnts;
  ShellShockParams *shockParams;
  AudioVolumeSetting *audioVolumeSetting;
  RadVerbPreset *reverbPreset;
  FogDef *fogDef;*/
  void *data;
};
}
