#include "Assets.h"

namespace Assets
{
	namespace SP_Dev
	{
#ifdef SP_DEV
		Util::Hook::Detour Load_PhysPresetPtr_Hook;
		void Load_PhysPresetPtr(bool atStreamStart)
		{
			auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			PhysPreset** varPhysPresetPtr = *(PhysPreset***)0x82C6E7E0;
			if (varPhysPresetPtr && *varPhysPresetPtr)
			{
#ifdef DUMP_ASSETS
				Dump_PhysPreset(*varPhysPresetPtr);
#elif LOAD_ASSETS
				Load_PhysPreset(*varPhysPresetPtr);
#endif
			}
		}

		Util::Hook::Detour Load_MapEntsPtr_Hook;
		void Load_MapEntsPtr(bool atStreamStart)
		{
			auto Invoke = Load_MapEntsPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			MapEnts** varMapEntsPtr = *(MapEnts***)0x82C6E7F8;
			if (varMapEntsPtr && *varMapEntsPtr)
			{
#ifdef DUMP_ASSETS
				Dump_MapEnts(*varMapEntsPtr);
#elif LOAD_ASSETS
				Load_MapEnts(*varMapEntsPtr);
#endif
			}
		}

union GfxTexture
{
  D3DBaseTexture basemap;
  D3DLineTexture linemap;
  D3DTexture map;
  D3DVolumeTexture volmap;
  D3DCubeTexture cubemap;
};

/* 5091 */
struct CardMemory
{
  int platform[1];
};

/* 5092 */
struct GfxImageStreamData
{
  unsigned __int16 width;
  unsigned __int16 height;
  unsigned int pixelSize;
};

/* 5093 */
struct GfxImage
{
  GfxTexture texture;
  int format;
  unsigned __int8 mapType;
  unsigned __int8 semantic;
  unsigned __int8 category;
  CardMemory cardMemory;
  unsigned __int16 width;
  unsigned __int16 height;
  unsigned __int16 depth;
  unsigned __int8 levelCount;
  unsigned __int8 cached;
  unsigned __int8 *pixels;
  GfxImageStreamData streams[4];
  const char *name;
};

// TODO: MAKEFOURCC('D', 'X', 'T', '1');
// DDS Constants
const uint32_t DDS_MAGIC = MAKEFOURCC('D', 'D', 'S', ' ');
const uint32_t DDS_HEADER_SIZE = 124;
const uint32_t DDS_PIXEL_FORMAT_SIZE = 32;
const uint32_t DDSD_CAPS = 0x1;
const uint32_t DDSD_HEIGHT = 0x2;
const uint32_t DDSD_WIDTH = 0x4;
const uint32_t DDSD_PIXELFORMAT = 0x1000;
const uint32_t DDSD_LINEARSIZE = 0x80000;
const uint32_t DDPF_FOURCC = 0x4;
const uint32_t DDPF_RGB = 0x40;
const uint32_t DDPF_ALPHAPIXELS = 0x1;
const uint32_t DDSCAPS_TEXTURE = 0x1000;
const uint32_t DDSCAPS_MIPMAP = 0x400000;
const uint32_t DDPF_LUMINANCE = 0x20000;

// DDS Pixel Formats (FourCC Codes)
const uint32_t DXT1_FOURCC = MAKEFOURCC('D', 'X', 'T', '1');
const uint32_t DXT3_FOURCC = MAKEFOURCC('D', 'X', 'T', '3');
const uint32_t DXT5_FOURCC = MAKEFOURCC('D', 'X', 'T', '5');
const uint32_t DXN_FOURCC = MAKEFOURCC('A', 'T', 'I', '2'); // (DXN / BC5)

// Additional DDS Cubemap Flags
const uint32_t DDSCAPS2_CUBEMAP = 0x200;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEX = 0x400;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEX = 0x800;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEY = 0x1000;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEY = 0x2000;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEZ = 0x4000;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x8000;

// DDS Header Structure (with inline endian swapping)
struct DDSHeader
{
    uint32_t magic;
    uint32_t size;
    uint32_t flags;
    uint32_t height;
    uint32_t width;
    uint32_t pitchOrLinearSize;
    uint32_t depth;
    uint32_t mipMapCount;
    uint32_t reserved1[11];
    struct
    {
        uint32_t size;
        uint32_t flags;
        uint32_t fourCC;
        uint32_t rgbBitCount;
        uint32_t rBitMask;
        uint32_t gBitMask;
        uint32_t bBitMask;
        uint32_t aBitMask;
    } pixelFormat;
    uint32_t caps;
    uint32_t caps2;
    uint32_t caps3;
    uint32_t caps4;
    uint32_t reserved2;
};

enum ugay : __int32
{
  MAPTYPE_NONE = 0x0,
  MAPTYPE_INVALID1 = 0x1,
  MAPTYPE_1D = 0x2,
  MAPTYPE_2D = 0x3,
  MAPTYPE_3D = 0x4,
  MAPTYPE_CUBE = 0x5,
  MAPTYPE_COUNT = 0x6,
};

	void GPUEndianSwapTexture(std::vector<uint8_t> &pixelData, GPUENDIAN endianType)
	{
		switch (endianType)
		{
		case GPUENDIAN_8IN16:
			XGEndianSwapMemory(pixelData.data(), pixelData.data(), XGENDIAN_8IN16, 2, pixelData.size() / 2);
			break;
		case GPUENDIAN_8IN32:
			XGEndianSwapMemory(pixelData.data(), pixelData.data(), XGENDIAN_8IN32, 4, pixelData.size() / 4);
			break;
		case GPUENDIAN_16IN32:
			XGEndianSwapMemory(pixelData.data(), pixelData.data(), XGENDIAN_16IN32, 4, pixelData.size() / 4);
			break;
		}
	}

size_t GetGfxImageSize(const GfxImage* image)
{
    auto format = image->texture.basemap.Format.DataFormat;

    switch (format)
    {
        case GPUTEXTUREFORMAT_DXT1:
        case GPUTEXTUREFORMAT_DXT2_3:
        case GPUTEXTUREFORMAT_DXT4_5:
        case GPUTEXTUREFORMAT_DXN:
        {
            size_t blockWidth  = (image->width + 3) / 4;
            size_t blockHeight = (image->height + 3) / 4;
            size_t bytesPerBlock = (format == GPUTEXTUREFORMAT_DXT1 ? 8 : 16);
            return blockWidth * blockHeight * bytesPerBlock;
        }
        case GPUTEXTUREFORMAT_8:
            return image->width * image->height;
        case GPUTEXTUREFORMAT_8_8:
            return image->width * image->height * 2;
        case GPUTEXTUREFORMAT_8_8_8_8:
            return image->width * image->height * 4;
        default:
            Symbols::SP_Dev::Com_Printf(1, "Unsupported texture format %d!\n", format);
            return 0;
    }
}

	void Dump_GfxImage(GfxImage* image)
	{
		if (!image)
		{
			Symbols::SP_Dev::Com_Printf(0, "Failed to dump image '%s' because fogDef was NULL\n", image->name);
			return;
		}

		Symbols::SP_Dev::Com_Printf(0, "Dumping image '%s'\n", image->name);

		UINT BaseSize;
		XGGetTextureLayout(&image->texture.basemap, 0, &BaseSize, 0, 0, 0, 0, 0, 0, 0, 0);

		DDSHeader header;
		memset(&header, 0, sizeof(DDSHeader));

		header.magic = _byteswap_ulong(DDS_MAGIC);
		header.size = _byteswap_ulong(DDS_HEADER_SIZE);
		header.flags = _byteswap_ulong(DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_LINEARSIZE);
		header.height = _byteswap_ulong(image->height);
		header.width = _byteswap_ulong(image->width);
		header.depth = _byteswap_ulong(image->depth);
		header.mipMapCount = _byteswap_ulong(image->texture.basemap.GetLevelCount());

		auto format = image->texture.basemap.Format.DataFormat;
		switch (format)
		{
		case GPUTEXTUREFORMAT_DXT1:
			header.pixelFormat.fourCC = _byteswap_ulong(DXT1_FOURCC);
			header.pitchOrLinearSize = BaseSize;
			break;
		case GPUTEXTUREFORMAT_DXT2_3:
			header.pixelFormat.fourCC = _byteswap_ulong(DXT3_FOURCC);
			header.pitchOrLinearSize = BaseSize;
			break;
		case GPUTEXTUREFORMAT_DXT4_5:
			header.pixelFormat.fourCC = _byteswap_ulong(DXT5_FOURCC);
			header.pitchOrLinearSize = BaseSize;
			break;
		case GPUTEXTUREFORMAT_DXN:
			header.pixelFormat.fourCC = _byteswap_ulong(DXN_FOURCC);
			header.pitchOrLinearSize = BaseSize;
			break;
		case GPUTEXTUREFORMAT_8:
			header.pixelFormat.flags = _byteswap_ulong(DDPF_LUMINANCE);
			header.pixelFormat.rgbBitCount = _byteswap_ulong(8);
			header.pixelFormat.rBitMask = _byteswap_ulong(0x000000FF);
			header.pixelFormat.gBitMask = 0;
			header.pixelFormat.bBitMask = 0;
			header.pixelFormat.aBitMask = 0;
			header.pitchOrLinearSize = BaseSize;
			break;
		case GPUTEXTUREFORMAT_8_8:
			header.pixelFormat.flags = _byteswap_ulong(DDPF_LUMINANCE | DDPF_ALPHAPIXELS);
			header.pixelFormat.rgbBitCount = _byteswap_ulong(16);
			header.pixelFormat.rBitMask = _byteswap_ulong(0x000000FF);
			header.pixelFormat.gBitMask = _byteswap_ulong(0x0000FF00);
			header.pixelFormat.bBitMask = 0;
			header.pixelFormat.aBitMask = 0;
			header.pitchOrLinearSize = BaseSize;
			break;
		case GPUTEXTUREFORMAT_8_8_8_8:
			header.pixelFormat.flags = _byteswap_ulong(DDPF_RGB | DDPF_ALPHAPIXELS);
			header.pixelFormat.rgbBitCount = _byteswap_ulong(32);
			header.pixelFormat.rBitMask = _byteswap_ulong(0x00FF0000);
			header.pixelFormat.gBitMask = _byteswap_ulong(0x0000FF00);
			header.pixelFormat.bBitMask = _byteswap_ulong(0x000000FF);
			header.pixelFormat.aBitMask = _byteswap_ulong(0xFF000000);
			header.pitchOrLinearSize = BaseSize;
			break;
		default:
			Symbols::SP_Dev::Com_Printf(1, "Unsupported texture format %d!\n", format);
			return;
		}

		// Set texture capabilities
		header.caps = _byteswap_ulong(DDSCAPS_TEXTURE | DDSCAPS_MIPMAP);

		// Handle Cubemaps
		if (image->mapType == MAPTYPE_CUBE)
		{
			header.caps2 = _byteswap_ulong(DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX | DDSCAPS2_CUBEMAP_NEGATIVEX |
										   DDSCAPS2_CUBEMAP_POSITIVEY | DDSCAPS2_CUBEMAP_NEGATIVEY |
										   DDSCAPS2_CUBEMAP_POSITIVEZ | DDSCAPS2_CUBEMAP_NEGATIVEZ);
		}

		std::string assetName = image->name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\" BASE_FOLDER "\\dump\\images\\" + assetName + ".dds";

		std::ofstream file(outPath, std::ios::binary);
		if (!file)
		{
			Symbols::SP_Dev::Com_Printf(1, "Failed to open file: %s\n", outPath);
			return;
		}

		if (image->mapType == MAPTYPE_CUBE)
		{
			file.write(reinterpret_cast<const char *>(&header), sizeof(DDSHeader));

			unsigned int face_size = 0;
			unsigned int rowPitch = 0;
			const GPUTEXTUREFORMAT format = static_cast<GPUTEXTUREFORMAT>(image->texture.basemap.Format.DataFormat);

			switch (format)
			{
			case GPUTEXTUREFORMAT_DXT1:
				face_size = (image->width / 4) * (image->height / 4) * 8;
				rowPitch = (image->width / 4) * 8; // 8 bytes per 4x4 block
				break;
			case GPUTEXTUREFORMAT_8_8_8_8:
				face_size = image->width * image->height * 4;
				rowPitch = image->width * 4; // 4 bytes per pixel
				break;
			default:
				Symbols::SP_Dev::Com_Printf(1, "Unsupported cube map format %d!\n", format);
				return;
			}

			// TODO: handle mip levels per face for cubemaps
			for (int i = 0; i < 6; i++)
			{
				unsigned char *face_pixels = image->pixels + (i * face_size); // Offset for each face

				std::vector<uint8_t> swappedFace(face_pixels, face_pixels + face_size);
				GPUEndianSwapTexture(swappedFace, static_cast<GPUENDIAN>(image->texture.basemap.Format.Endian));

				// Create buffer for linear texture data
				std::vector<uint8_t> linearFace(face_size);

				// Convert tiled texture to linear layout using XGUntileTextureLevel
				XGUntileTextureLevel(image->width,               // Width
									 image->height,              // Height
									 0,                          // Level (base level)
									 static_cast<DWORD>(format), // GpuFormat
									 0,                          // Flags (no special flags)
									 linearFace.data(),          // pDestination (linear output)
									 rowPitch,                   // RowPitch
									 nullptr,                    // pPoint (no offset)
									 swappedFace.data(),         // pSource (tiled input)
									 nullptr                     // pRect (entire texture)
				);

				file.write(reinterpret_cast<const char *>(linearFace.data()), linearFace.size());
			}

			file.close();
		}
		else if (image->mapType == MAPTYPE_2D)
		{
			// TODO: write mip levels
			file.write(reinterpret_cast<const char *>(&header), sizeof(DDSHeader));

size_t imageSize = GetGfxImageSize(image);
std::vector<uint8_t> pixelData(image->pixels, image->pixels + imageSize);
std::vector<uint8_t> linearData(imageSize);

			GPUEndianSwapTexture(pixelData, static_cast<GPUENDIAN>(image->texture.basemap.Format.Endian));

			// Create a linear data buffer to hold the untiled texture

			// Calculate row pitch based on format
			UINT rowPitch;
			auto format = image->texture.basemap.Format.DataFormat;

			switch (format)
			{
			case GPUTEXTUREFORMAT_DXT1:
			case GPUTEXTUREFORMAT_DXT2_3:
			case GPUTEXTUREFORMAT_DXT4_5:
			case GPUTEXTUREFORMAT_DXN:
				// Block compressed formats use 4x4 blocks
				rowPitch = ((image->width + 3) / 4) * (format == GPUTEXTUREFORMAT_DXT1 ? 8 : 16);
				break;
			case GPUTEXTUREFORMAT_8:
				rowPitch = image->width;
				break;
			case GPUTEXTUREFORMAT_8_8:
				rowPitch = image->width * 2;
				break;
			case GPUTEXTUREFORMAT_8_8_8_8:
				rowPitch = image->width * 4;
				break;
			default:
				Symbols::SP_Dev::Com_Printf(1, "Unsupported texture format %d!\n", format);
				return;
			}

			Symbols::SP_Dev::Com_Printf(1, "rowPitch=%d\n", rowPitch);

			// Call XGUntileTextureLevel to convert the tiled texture to linear format
			XGUntileTextureLevel(image->width,               // Width
								 image->height,              // Height
								 0,                          // Level (base level 0)
								 static_cast<DWORD>(format), // GpuFormat
								 XGTILE_NONPACKED,           // Flags (no special flags)
								 linearData.data(),          // pDestination
								 rowPitch,                   // RowPitch (calculated based on format)
								 nullptr,                    // pPoint (no offset)
								 pixelData.data(),           // pSource
								 nullptr                     // pRect (entire texture)
			);

			file.write(reinterpret_cast<const char *>(linearData.data()), linearData.size());

			file.close();
		}
		else
		{
			Symbols::SP_Dev::Com_Printf(1, "Unsupported map type %d!\n", image->mapType);
			return;
		}
	}

		Util::Hook::Detour Load_MapEnts2Ptr_Hook;
		void Load_MapEnts2Ptr(bool atStreamStart)
		{
			auto Invoke = Load_MapEnts2Ptr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			GfxImage** varMapEntsPtr = *(GfxImage***)0x82C6E94C;
			if (varMapEntsPtr && *varMapEntsPtr)
			{
//#ifdef DUMP_ASSETS
				Dump_GfxImage(*varMapEntsPtr);
//#elif LOAD_ASSETS
//				Load_MapEnts(*varMapEntsPtr);
//#endif
			}
		}

		Util::Hook::Detour Load_LocalizeEntryPtr_Hook;
		void Load_LocalizeEntryPtr(bool atStreamStart)
		{
			auto Invoke = Load_LocalizeEntryPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			LocalizeEntry** varLocalizeEntryPtr = *(LocalizeEntry***)0x82C6E95C;
			if (!varLocalizeEntryPtr || !*varLocalizeEntryPtr)
			{
#ifdef DUMP_ASSETS
				Dump_LocalizeEntry(*varLocalizeEntryPtr);
#elif LOAD_ASSETS
				Load_LocalizeEntry(*varLocalizeEntryPtr);
#endif
			}
		}

		Util::Hook::Detour DB_GetRawBuffer_Hook;
		void DB_GetRawBuffer(const RawFile* rawFile, char* buffer, int size)
		{
			auto Invoke = DB_GetRawBuffer_Hook.Invoke<void(*)(const RawFile*, char*, int)>();
			
			// TODO: put this behind a dvar
			// override the file if it exists
			RawFile* loaded = LoadRawFiles(rawFile->name);
			if (loaded)
			{
				int copySize = (size < loaded->len) ? size : loaded->len;
				memcpy(buffer, loaded->buffer, copySize);

				FreeRawFiles(loaded);
				return;
			}

			// TODO: put this behind a dvar
			//DumpRawFiles(rawFile, buffer, size);

			Invoke(rawFile, buffer, size);
		}

		Util::Hook::Detour Load_StringTablePtr_Hook;
		void Load_StringTablePtr(bool atStreamStart)
		{
			auto Invoke = Load_StringTablePtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			StringTable** varStringTablePtr = *(StringTable***)0x82C6DF5C;
			if (varStringTablePtr && *varStringTablePtr)
			{
#ifdef DUMP_ASSETS
				Dump_StringTable(*varStringTablePtr);
#elif LOAD_ASSETS
				Load_StringTable(*varStringTablePtr);
#endif
			}
		}

		Util::Hook::Detour Load_TracerDefPtr_Hook;
		void Load_TracerDefPtr(bool atStreamStart)
		{
			auto Invoke = Load_TracerDefPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			TracerDef** varTracerDefPtr = *(TracerDef***)0x82C6E834;
			if (varTracerDefPtr && *varTracerDefPtr)
			{
#ifdef DUMP_ASSETS
				Dump_TracerDef(*varTracerDefPtr);
#elif LOAD_ASSETS
				Load_TracerDef(*varTracerDefPtr);
#endif
			}
		}

		Util::Hook::Detour Load_ShellshockParamsPtr_Hook;
		void Load_ShellshockParamsPtr(bool atStreamStart)
		{
			auto Invoke = Load_ShellshockParamsPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			ShellShockParams** varShellshockParamsPtr = *(ShellShockParams***)0x82C6E580;
			if (varShellshockParamsPtr && *varShellshockParamsPtr)
			{
#ifdef DUMP_ASSETS
				Dump_ShellshockParams(*varShellshockParamsPtr);
#elif LOAD_ASSETS
				Load_ShellshockParams(*varShellshockParamsPtr);
#endif
			}
		}

		Util::Hook::Detour Load_FogDefPtr_Hook;
		void Load_FogDefPtr(bool atStreamStart)
		{
			auto Invoke = Load_FogDefPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			FogDef** varFogDefPtr = *(FogDef***)0x82C6DF24;
			if (varFogDefPtr && *varFogDefPtr)
			{
#ifdef DUMP_ASSETS
				Dump_FogDef(*varFogDefPtr);
#elif LOAD_ASSETS
				Load_FogDef(*varFogDefPtr);
#endif
			}
		}

		void Hooks()
		{
			Load_PhysPresetPtr_Hook.Create(0x82250C00, Load_PhysPresetPtr);
			// ASSET_TYPE_PHYSCOLLMAP
			// ASSET_TYPE_XANIMPARTS
			// ASSET_TYPE_XMODEL_SURFS
			// ASSET_TYPE_XMODEL
			// ASSET_TYPE_MATERIAL
			// ASSET_TYPE_PIXELSHADER
			// ASSET_TYPE_TECHNIQUE_SET
			Load_MapEnts2Ptr_Hook.Create(0x82249638, Load_MapEnts2Ptr);
			// ASSET_TYPE_SOUND
			// ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE
			// ASSET_TYPE_SND_LPF_CURVE
			// ASSET_TYPE_LOADED_SOUND
			// ASSET_TYPE_CLIPMAP_SP
			// ASSET_TYPE_CLIPMAP_MP
			// ASSET_TYPE_COMWORLD
			// ASSET_TYPE_GAMEWORLD_SP
			// ASSET_TYPE_GAMEWORLD_MP
			Load_MapEntsPtr_Hook.Create(0x82259EF0, Load_MapEntsPtr);
			// ASSET_TYPE_FXWORLD
			// ASSET_TYPE_GFXWORLD
			// ASSET_TYPE_LIGHT_DEF
			// ASSET_TYPE_UI_MAP
			// ASSET_TYPE_FONT
			// ASSET_TYPE_MENULIST
			// ASSET_TYPE_MENU
			Load_LocalizeEntryPtr_Hook.Create(0x8225FD28, Load_LocalizeEntryPtr);
			// ASSET_TYPE_WEAPON
			// ASSET_TYPE_SNDDRIVER_GLOBALS
			// ASSET_TYPE_FX
			// ASSET_TYPE_IMPACT_FX
			// ASSET_TYPE_SURFACE_FX
			// ASSET_TYPE_AITYPE
			// ASSET_TYPE_MPTYPE
			// ASSET_TYPE_CHARACTER
			// ASSET_TYPE_XMODELALIAS
			DB_GetRawBuffer_Hook.Create(0x82288630, DB_GetRawBuffer);
			Load_StringTablePtr_Hook.Create(0x82263550, Load_StringTablePtr);
			// ASSET_TYPE_LEADERBOARD
			// ASSET_TYPE_STRUCTURED_DATA_DEF
			Load_TracerDefPtr_Hook.Create(0x822603F0, Load_TracerDefPtr);
			// ASSET_TYPE_LASER
			// ASSET_TYPE_VEHICLE
			// ASSET_TYPE_ADDON_MAP_ENTS
			Load_ShellshockParamsPtr_Hook.Create(0x8226C5C0, Load_ShellshockParamsPtr);
			// ASSET_TYPE_VOLUMESETTING
			// ASSET_TYPE_REVERBPRESET
			Load_FogDefPtr_Hook.Create(0x82265E28, Load_FogDefPtr);
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
		}
#endif
	}

	namespace MP_Dev
	{
#ifdef MP_DEV
		// TODO
#endif
	}

	namespace SP_Demo
	{
#ifdef SP_DEMO
		// TODO
#endif
	}

	namespace MP_Demo
	{
#ifdef MP_DEMO
		Util::Hook::Detour Load_PhysPresetPtr_Hook;
		void Load_PhysPresetPtr(bool atStreamStart)
		{
			auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			PhysPreset** varPhysPresetPtr = *(PhysPreset***)0x828BE9E0;
			if (varPhysPresetPtr && *varPhysPresetPtr)
			{
#ifdef DUMP_ASSETS
				Dump_PhysPreset(*varPhysPresetPtr);
#elif LOAD_ASSETS
				Load_PhysPreset(*varPhysPresetPtr);
#endif
			}
		}

		Util::Hook::Detour Load_MapEntsPtr_Hook;
		void Load_MapEntsPtr(bool atStreamStart)
		{
			auto Invoke = Load_MapEntsPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			MapEnts** varMapEntsPtr = *(MapEnts***)0x828BE9F8;
			if (varMapEntsPtr && *varMapEntsPtr)
			{
#ifdef DUMP_ASSETS
				Dump_MapEnts(*varMapEntsPtr);
#elif LOAD_ASSETS
				Load_MapEnts(*varMapEntsPtr);
#endif
			}
		}

		Util::Hook::Detour Load_LocalizeEntryPtr_Hook;
		void Load_LocalizeEntryPtr(bool atStreamStart)
		{
			auto Invoke = Load_LocalizeEntryPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			LocalizeEntry** varLocalizeEntryPtr = *(LocalizeEntry***)0x828BEB5C;
			if (!varLocalizeEntryPtr || !*varLocalizeEntryPtr)
			{
#ifdef DUMP_ASSETS
				Dump_LocalizeEntry(*varLocalizeEntryPtr);
#elif LOAD_ASSETS
				Load_LocalizeEntry(*varLocalizeEntryPtr);
#endif
			}
		}

		Util::Hook::Detour DB_GetRawBuffer_Hook;
		void DB_GetRawBuffer(const RawFile* rawFile, char* buffer, int size)
		{
			auto Invoke = DB_GetRawBuffer_Hook.Invoke<void(*)(const RawFile*, char*, int)>();
			/*
			// TODO: put this behind a dvar
			// override the file if it exists
			RawFile* loaded = LoadRawFiles(rawFile->name);
			if (loaded)
			{
				int copySize = (size < loaded->len) ? size : loaded->len;
				memcpy(buffer, loaded->buffer, copySize);

				FreeRawFiles(loaded);
				return;
			}*/

			// TODO: put this behind a dvar
			//DumpRawFiles(rawFile, buffer, size);

			Invoke(rawFile, buffer, size);
		}

		Util::Hook::Detour Load_StringTablePtr_Hook;
		void Load_StringTablePtr(bool atStreamStart)
		{
			auto Invoke = Load_StringTablePtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			StringTable** varStringTablePtr = *(StringTable***)0x828BE15C;
			if (varStringTablePtr && *varStringTablePtr)
			{
#ifdef DUMP_ASSETS
				Dump_StringTable(*varStringTablePtr);
#elif LOAD_ASSETS
				Load_StringTable(*varStringTablePtr);
#endif
			}
		}

		Util::Hook::Detour Load_TracerDefPtr_Hook;
		void Load_TracerDefPtr(bool atStreamStart)
		{
			auto Invoke = Load_TracerDefPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			TracerDef** varTracerDefPtr = *(TracerDef***)0x828BEA34;
			if (varTracerDefPtr && *varTracerDefPtr)
			{
#ifdef DUMP_ASSETS
				Dump_TracerDef(*varTracerDefPtr);
#elif LOAD_ASSETS
				Load_TracerDef(*varTracerDefPtr);
#endif
			}
		}

		Util::Hook::Detour Load_ShellshockParamsPtr_Hook;
		void Load_ShellshockParamsPtr(bool atStreamStart)
		{
			auto Invoke = Load_ShellshockParamsPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			ShellShockParams** varShellshockParamsPtr = *(ShellShockParams***)0x828BE780;
			if (varShellshockParamsPtr && *varShellshockParamsPtr)
			{
#ifdef DUMP_ASSETS
				Dump_ShellshockParams(*varShellshockParamsPtr);
#elif LOAD_ASSETS
				Load_ShellshockParams(*varShellshockParamsPtr);
#endif
			}
		}

		Util::Hook::Detour Load_FogDefPtr_Hook;
		void Load_FogDefPtr(bool atStreamStart)
		{
			auto Invoke = Load_FogDefPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			FogDef** varFogDefPtr = *(FogDef***)0x828BE124;
			if (varFogDefPtr && *varFogDefPtr)
			{
#ifdef DUMP_ASSETS
				Dump_FogDef(*varFogDefPtr);
#elif LOAD_ASSETS
				Load_FogDef(*varFogDefPtr);
#endif
			}
		}

		void Hooks()
		{
			Load_PhysPresetPtr_Hook.Create(0x821E1F00, Load_PhysPresetPtr);
			// ASSET_TYPE_PHYSCOLLMAP
			// ASSET_TYPE_XANIMPARTS
			// ASSET_TYPE_XMODEL_SURFS
			// ASSET_TYPE_XMODEL
			// ASSET_TYPE_MATERIAL
			// ASSET_TYPE_PIXELSHADER
			// ASSET_TYPE_TECHNIQUE_SET
			// ASSET_TYPE_IMAGE = 0x8,
			// ASSET_TYPE_SOUND = 0x9,
			// ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE
			// ASSET_TYPE_SND_LPF_CURVE
			// ASSET_TYPE_LOADED_SOUND
			// ASSET_TYPE_CLIPMAP_SP
			// ASSET_TYPE_CLIPMAP_MP
			// ASSET_TYPE_COMWORLD
			// ASSET_TYPE_GAMEWORLD_SP
			// ASSET_TYPE_GAMEWORLD_MP
			Load_MapEntsPtr_Hook.Create(0x821EA608, Load_MapEntsPtr);
			// ASSET_TYPE_FXWORLD
			// ASSET_TYPE_GFXWORLD
			// ASSET_TYPE_LIGHT_DEF
			// ASSET_TYPE_UI_MAP
			// ASSET_TYPE_FONT
			// ASSET_TYPE_MENULIST
			// ASSET_TYPE_MENU
			Load_LocalizeEntryPtr_Hook.Create(0x821EFC90, Load_LocalizeEntryPtr);
			// ASSET_TYPE_WEAPON
			// ASSET_TYPE_SNDDRIVER_GLOBALS
			// ASSET_TYPE_FX
			// ASSET_TYPE_IMPACT_FX
			// ASSET_TYPE_SURFACE_FX
			// ASSET_TYPE_AITYPE
			// ASSET_TYPE_MPTYPE
			// ASSET_TYPE_CHARACTER
			// ASSET_TYPE_XMODELALIAS
			DB_GetRawBuffer_Hook.Create(0x822140E0, DB_GetRawBuffer);
			Load_StringTablePtr_Hook.Create(0x821F2F18, Load_StringTablePtr);
			// ASSET_TYPE_LEADERBOARD
			// ASSET_TYPE_STRUCTURED_DATA_DEF
			Load_TracerDefPtr_Hook.Create(0x821F0308, Load_TracerDefPtr);
			// ASSET_TYPE_LASER
			// ASSET_TYPE_VEHICLE
			// ASSET_TYPE_ADDON_MAP_ENTS
			Load_ShellshockParamsPtr_Hook.Create(0x821FB5D0, Load_ShellshockParamsPtr);
			// ASSET_TYPE_VOLUMESETTING
			// ASSET_TYPE_REVERBPRESET
			Load_FogDefPtr_Hook.Create(0x821F5488, Load_FogDefPtr);
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
		}
#endif
	}
}
