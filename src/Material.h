#pragma once

#include "GothicTools.h"

#include "Color.h"
#include "Object.h"

enum zTMat_Group
{
	zMAT_GROUP_UNDEF,
	zMAT_GROUP_METAL,
	zMAT_GROUP_STONE,
	zMAT_GROUP_WOOD,
	zMAT_GROUP_EARTH,
	zMAT_GROUP_WATER,
	zMAT_GROUP_SNOW,
	zMAT_NUM_MAT_GROUP,
};

enum zTWaveAniMode
{
	zWAVEANI_NONE,
	zWAVEANI_GROUND_AMBIENT,
	zWAVEANI_GROUND,
	zWAVEANI_WALL_AMBIENT,
	zWAVEANI_WALL,
	zWAVEANI_ENV,
	zWAVEANI_WIND_AMBIENT,
	zWAVEANI_WIND,
};

enum zTFFT
{
	zTFFT_NONE,
	zTFFT_SLOW,
	zTFFT_NORMAL,
	zTFFT_FAST,
};

enum zTRnd_AlphaBlendFunc
{
	zRND_ALPHA_FUNC_MAT_DEFAULT,
	zRND_ALPHA_FUNC_NONE,
	zRND_ALPHA_FUNC_BLEND,
	zRND_ALPHA_FUNC_ADD,
	zRND_ALPHA_FUNC_SUB,
	zRND_ALPHA_FUNC_MUL,
	zRND_ALPHA_FUNC_MUL2,
	zRND_ALPHA_FUNC_TEST,
	zRND_ALPHA_FUNC_BLEND_TEST
};

class zCMaterial : public zCObject
{
public:
	static const zSTRING GetClassName() { return "zCMaterial"; }

public:
	zSTRING name;

	zSTRING texture;
	zCOLOR color;
	float smoothAngle;
	zTMat_Group matGroup;
	float aniFPS;

	float m_bEnvironmentalMappingStrength;

	uint8 dontUseLightmaps;
	uint8 texAniMap;
	uint8 lodDontCollapse;
	uint8 noCollDet;
	uint8 forceOccluder;
	uint8 m_bEnvironmentalMapping;
	uint8 polyListNeedsSort;
	uint8 libFlag;
	zTRnd_AlphaBlendFunc rndAlphaBlendFunc;
	uint8 m_bIgnoreSun;

	zTWaveAniMode m_enuWaveMode;
	zTFFT m_enuWaveSpeed;
	float m_fWaveMaxAmplitude;
	float m_fWaveGridSize;

	zSTRING detailTexture;
	float detailTextureScale;
	zSTRING texAniMapDelta;

	zPOINT2 default_mapping;
	zSTRING texScale;

public:
	zCMaterial() { InitValues(); }
	zCMaterial(const zSTRING &n) { InitValues(); name = n; }

	void InitValues();
	bool32 Unarchive(zCFileBIN &file);
	void Archive(zCFileBIN &file, uint32 objectIndex);
};

