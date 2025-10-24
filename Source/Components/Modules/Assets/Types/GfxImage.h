#pragma once

namespace Assets
{
	union GfxTexture
	{
		D3DBaseTexture basemap;
		D3DLineTexture linemap;
		D3DTexture map;
		D3DVolumeTexture volmap;
		D3DCubeTexture cubemap;
	};

	enum MapType : int
	{
		MAPTYPE_NONE = 0x0,
		MAPTYPE_INVALID1 = 0x1,
		MAPTYPE_1D = 0x2,
		MAPTYPE_2D = 0x3,
		MAPTYPE_3D = 0x4,
		MAPTYPE_CUBE = 0x5,

		MAPTYPE_COUNT = 0x6,
	};

	struct CardMemory
	{
		int platform[1];
	};

	struct GfxImageStreamData
	{
		unsigned short width;
		unsigned short height;
		unsigned int pixelSize;
	};

	struct GfxImage
	{
		GfxTexture texture;
		MapType format;
		unsigned char mapType;
		unsigned char semantic;
		unsigned char category;
		CardMemory cardMemory;
		unsigned short width;
		unsigned short height;
		unsigned short depth;
		unsigned char levelCount;
		unsigned char cached;
		unsigned char* pixels;
		GfxImageStreamData streams[4];
		const char* name;
	};
}
