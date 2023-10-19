#include "Material.h"

bool32 zCMaterial::Unarchive(zCArchiver &arc)
{
	if (!zCObject::Unarchive(arc)) return FALSE;

	if (chunk.classVersion != materialVersionIn
		&& ((materialVersionIn == MATERIAL_CLASS_VERSION_GOTHIC_1_30 && chunk.classVersion != MATERIAL_CLASS_VERSION_GOTHIC_OLD1)
		&& (materialVersionIn == MATERIAL_CLASS_VERSION_GOTHIC_1_30 && chunk.classVersion != MATERIAL_CLASS_VERSION_GOTHIC_OLD2)))
	{
		printf("Wrong Material version\n");

		return FALSE;
	}

	arc.ReadString("name", name);
	arc.ReadEnum("matGroup", matGroup);
	arc.ReadColor("color", color);
	arc.ReadFloat("smoothAngle", smoothAngle);

	arc.ReadString("texture", texture);
	arc.ReadString("texScale", texScale);
	arc.ReadFloat("texAniFPS", texAniFPS);
	arc.ReadEnum("texAniMapMode", texAniMapMode);
	arc.ReadString("texAniMapDir", texAniMapDir);

	arc.ReadBool("noCollDet", noCollDet);
	arc.ReadBool("noLightmap", noLightmap);
	arc.ReadBool("lodDontCollapse", lodDontCollapse);

	arc.ReadString("detailObject", detailObject);

	if (materialVersionIn == MATERIAL_CLASS_VERSION_GOTHIC_1_01 || materialVersionIn == MATERIAL_CLASS_VERSION_GOTHIC_1_04
		|| chunk.classVersion == MATERIAL_CLASS_VERSION_GOTHIC_OLD1 || chunk.classVersion == MATERIAL_CLASS_VERSION_GOTHIC_OLD2)
	{
		alphaFunc = color.alpha == 0xFF ? zRND_ALPHA_FUNC_NONE : zRND_ALPHA_FUNC_BLEND;

		if (matGroup == zMAT_GROUP_WATER && alphaFunc == zRND_ALPHA_FUNC_NONE)
		{
			alphaFunc = zRND_ALPHA_FUNC_BLEND;
		}
	}

	if (materialVersionIn == MATERIAL_CLASS_VERSION_GOTHIC_1_30)
	{
		arc.ReadFloat("detailObjectScale", detailObjectScale);

		arc.ReadBool("forceOccluder", forceOccluder);
		arc.ReadBool("environmentalMapping", environmentalMapping);
		arc.ReadFloat("environmentalMappingStrength", environmentalMappingStrength);

		arc.ReadEnum("waveMode", waveMode);
		arc.ReadEnum("waveSpeed", waveSpeed);

		if (chunk.classVersion == MATERIAL_CLASS_VERSION_GOTHIC_OLD1)
		{
			uint16 w;

			arc.ReadWord("waveMaxAmplitude", w);
			waveMaxAmplitude = w;

			arc.ReadWord("waveGridSize", w);
			waveGridSize = w;
		}
		else
		{
			arc.ReadFloat("waveMaxAmplitude", waveMaxAmplitude);
			arc.ReadFloat("waveGridSize", waveGridSize);
		}

		arc.ReadBool("ignoreSunLight", ignoreSunLight);

		if (chunk.classVersion != MATERIAL_CLASS_VERSION_GOTHIC_OLD1 && chunk.classVersion != MATERIAL_CLASS_VERSION_GOTHIC_OLD2)
		{
			arc.ReadEnum("alphaFunc", alphaFunc);
		}
	}
	else
	{
		detailObjectScale = 1.0f;

		forceOccluder = FALSE;
		environmentalMapping = FALSE;
		environmentalMappingStrength = 1.0f;

		waveMode = zWAVEANI_NONE;
		waveSpeed = zTFFT_NORMAL;
		waveMaxAmplitude = 30.0f;
		waveGridSize = 100.0f;

		ignoreSunLight = FALSE;
	}

	arc.ReadRawFloat("defaultMapping", &defaultMapping, sizeof(defaultMapping));

	return TRUE;
}

void zCMaterial::Archive(zCArchiver &arc)
{
	zCObject::Archive(arc);

	arc.WriteString("name", name);
	arc.WriteEnum("matGroup", matGroup);
	arc.WriteColor("color", color);
	arc.WriteFloat("smoothAngle", smoothAngle);

	arc.WriteString("texture", texture);
	arc.WriteString("texScale", texScale);
	arc.WriteFloat("texAniFPS", texAniFPS);
	arc.WriteEnum("texAniMapMode", texAniMapMode);
	arc.WriteString("texAniMapDir", texAniMapDir);

	arc.WriteBool("noCollDet", noCollDet);
	arc.WriteBool("noLightmap", noLightmap);
	arc.WriteBool("lodDontCollapse", lodDontCollapse);

	arc.WriteString("detailObject", detailObject);

	if (materialVersionOut == MATERIAL_CLASS_VERSION_GOTHIC_1_30)
	{
		arc.WriteFloat("detailObjectScale", detailObjectScale);

		arc.WriteBool("forceOccluder", forceOccluder);
		arc.WriteBool("environmentalMapping", environmentalMapping);
		arc.WriteFloat("environmentalMappingStrength", environmentalMappingStrength);

		arc.WriteEnum("waveMode", waveMode);
		arc.WriteEnum("waveSpeed", waveSpeed);

		arc.WriteFloat("waveMaxAmplitude", waveMaxAmplitude);
		arc.WriteFloat("waveGridSize", waveGridSize);

		arc.WriteBool("ignoreSunLight", ignoreSunLight);

		arc.WriteEnum("alphaFunc", alphaFunc);
	}

	arc.WriteRawFloat("defaultMapping", &defaultMapping, sizeof(defaultMapping));
}