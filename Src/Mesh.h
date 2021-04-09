#pragma once

#define zFCHUNK_MESH ((uint16)0xB000)
#define zFCHUNK_BBOX3D ((uint16)0xB010)
#define zFCHUNK_MATLIST ((uint16)0xB020)
#define zFCHUNK_LIGHTMAPLIST ((uint16)0xB025)
#define zFCHUNK_LIGHTMAPLIST_SHARED ((uint16)0xB026)
#define zFCHUNK_VERTLIST ((uint16)0xB030)
#define zFCHUNK_FEATLIST ((uint16)0xB040)
#define zFCHUNK_POLYLIST ((uint16)0xB050)
#define zFCHUNK_MESH_END ((uint16)0xB060)

class zCMesh
{
public:
	zSTRING name;
	zDATE date;

	bool32 hasLightmaps;
	bool32 m_bUsesAlphaTesting;

	zTBBox3D bbox3D;
	zCOBBox3D obbox3D;

	zCArray<zCMaterial *> matList;

	int32 numPoly;
	int32 numVert;
	int32 numFeat;

	zCPolygon **polyArray;
	zCVertex *vertArray;
	zCVertFeature *featArray;

	int32 lightMapsLen;
	byte *lightMaps;

public:
	zCMesh();
	~zCMesh();

	bool32 UnarchiveMatList(zCFileBIN &file);
	void ArchiveMatList(zCFileBIN &file);

	void UnarchivePolyList(zCFileBIN &file, int32 len);
	void ArchivePolyList(zCFileBIN &file);

	void LODDegenerate(int32 *polyIndexMap, int32 newNumPoly);

	bool32 LoadMSH(const zSTRING &fileName) { zCFileBIN f(fileName); return LoadMSH(f); }
	bool32 LoadMSH(zCFileBIN &file);

	bool32 SaveMSH(const zSTRING &fileName) { zCFileBIN f(fileName, TRUE); return SaveMSH(f); }
	bool32 SaveMSH(zCFileBIN &file);
};
