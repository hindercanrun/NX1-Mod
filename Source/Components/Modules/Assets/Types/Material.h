#pragma once

namespace Assets
{
	struct GfxDrawSurfFields
	{
		unsigned long long objectId : 16;
		unsigned long long reflectionProbeIndex : 8;
		unsigned long long hasGfxEntIndex : 1;
		unsigned long long customIndex : 5;
		unsigned long long materialSortedIndex : 12;
		unsigned long long prepass : 2;
		unsigned long long useHeroLighting : 1;
		unsigned long long sceneLightIndex : 8;
		unsigned long long surfType : 4;
		unsigned long long primarySortKey : 6;
		unsigned long long unused : 1;
	};

	union GfxDrawSurf
	{
		GfxDrawSurfFields fields;
		unsigned long long packed;
	};

	struct MaterialInfo
	{
		const char* name;
		unsigned long gameFlags;
		unsigned char sortKey;
		unsigned char textureAtlasRowCount;
		unsigned char textureAtlasColumnCount;
		unsigned char textureAtlasFrameBlend;
		GfxDrawSurf drawSurf;
		unsigned int surfaceTypeBits;
	};

	struct MaterialPass
	{
		//MaterialVertexDeclaration* vertexDecl;
		//MaterialVertexShader* vertexShaderArray[17];
		//MaterialVertexShader* vertexShader;
		//MaterialPixelShader* pixelShader;
		unsigned char perPrimArgCount;
		unsigned char perObjArgCount;
		unsigned char stableArgCount;
		unsigned char customSamplerFlags;
		unsigned char precompiledIndex;
		//MaterialShaderArgument* args;
	};

	struct MaterialTechnique
	{
		const char* name;
		unsigned long flags;
		unsigned long passCount;
		MaterialPass passArray[1];
	};

	struct MaterialTechniqueSet
	{
		const char* name;
		unsigned char worldVertFormat;
		unsigned char unused[2];
		MaterialTechniqueSet* remappedTechniqueSet;
		MaterialTechnique* techniques[52];
	};

	union MaterialTextureDefInfo
	{
		//GfxImage* image;
		//water_t* water;
	};

	struct MaterialTextureDef
	{
		unsigned int nameHash;
		char nameStart;
		char nameEnd;
		unsigned char samplerState;
		unsigned char m_semantic;
		MaterialTextureDefInfo u;
		//GfxImage* mp_override_image;
		unsigned int m_override_image;
	};

	struct MaterialConstantDef
	{
		unsigned int nameHash;
		char name[12];
		float literal[4];
	};

	struct GfxStateBits
	{
		unsigned int loadBits[3];
	};

	struct Material
	{
		MaterialInfo info;
		unsigned char stateBitsEntry[52];
		unsigned char textureCount;
		unsigned char constantCount;
		unsigned char stateBitsCount;
		unsigned char stateFlags;
		unsigned char cameraRegion;
		unsigned char layerCount;
		MaterialTechniqueSet* techniqueSet;
		MaterialTextureDef* textureTable;
		MaterialConstantDef* constantTable;
		GfxStateBits* stateBitsTable;
		const char** subMaterials;
	};

	//void Dump_PhysPreset(const PhysPreset* physPreset);
}
