#pragma once

#define zFCHUNK_MESH ((zWORD)0xB000)
#define zFCHUNK_BBOX3D ((zWORD)0xB010)
#define zFCHUNK_MATLIST ((zWORD)0xB020)
#define zFCHUNK_LIGHTMAPLIST ((zWORD)0xB025)
#define zFCHUNK_LIGHTMAPLIST_SHARED ((zWORD)0xB026)
#define zFCHUNK_VERTLIST ((zWORD)0xB030)
#define zFCHUNK_FEATLIST ((zWORD)0xB040)
#define zFCHUNK_POLYLIST ((zWORD)0xB050)
#define zFCHUNK_MESH_END ((zWORD)0xB060)

class zCMesh
{
public:
	zSTRING name;
	zDATE date;

	zBOOL hasLightmaps;
	zBOOL m_bUsesAlphaTesting;

	zTBBox3D bbox3D;
	zCOBBox3D obbox3D;

	zCArray<zCMaterial *> matList;

	zINT numPoly;
	zINT numVert;
	zINT numFeat;

	zCPolygon **polyArray;
	zCVertex *vertArray;
	zCVertFeature *featArray;

	zLONG lightMapsLen;
	byte *lightMaps;

public:
	zCMesh();
	~zCMesh();

	zBOOL UnarchiveMatList(zCFileBIN &file);
	void ArchiveMatList(zCFileBIN &file);

	void UnarchivePolyList(zCFileBIN &file, zLONG len);
	void ArchivePolyList(zCFileBIN &file);

	void LODDegenerate(zINT *polyIndexMap, zINT newNumPoly);

	zBOOL LoadMSH(const zSTRING &fileName) { zCFileBIN f(fileName); return LoadMSH(f); }
	zBOOL LoadMSH(zCFileBIN &file);

	zBOOL SaveMSH(const zSTRING &fileName) { zCFileBIN f(fileName, TRUE); return SaveMSH(f); }
	zBOOL SaveMSH(zCFileBIN &file);
};
