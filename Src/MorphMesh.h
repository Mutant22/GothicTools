#pragma once

class zCMorphMeshAni
{
public:
	zSTRING aniName;

	zREAL blendInSpeed;
	zREAL blendOutSpeed;
	zREAL holdTime;
	zINT layer;
	zREAL fpsRate;

	struct
	{
		zUINT8 discontinuity : 1;
		zUINT8 looping : 1;
		zUINT8 shape : 1;
		zUINT8 refShape : 1;
	} flags;

	zINT numVert;
	zINT *vertIndexList;

	zINT numFrames;
	zPOINT3 *vertPosMatrix;

public:
	zCMorphMeshAni()
	{
		vertIndexList = NULL;
		vertPosMatrix = NULL;

		memset(&flags, 0x00, sizeof(flags));
	}

	~zCMorphMeshAni()
	{
		zFREE(vertIndexList);
		zDELETE_ARRAY(vertPosMatrix);
	}

	zVOID Load(zCFileBIN &file);
	zVOID Save(zCFileBIN &file);
};

#define zFCHUNK_MMB_MORPHMESH ((zWORD)0xE000)
#define zFCHUNK_MMB_SOURCE ((zWORD)0xE010)
#define zFCHUNK_MMB_HEADER ((zWORD)0xE020)
#define zFCHUNK_MMB_ANILIST ((zWORD)0xE030)

class zCMorphMeshProto
{
public:
	zSTRING morphProtoName;
	zCProgMeshProto *morphRefMesh;
	zPOINT3 *morphRefMeshVertPos;

	zWORD numAni;
	zTSrcFileStats *srcFileStats;
	zCArray<zCMorphMeshAni *> aniList;

public:
	zCMorphMeshProto()
	{
		morphRefMesh = NULL;
		morphRefMeshVertPos = NULL;
		srcFileStats = NULL;
	}

	~zCMorphMeshProto()
	{
		zDELETE(morphRefMesh);
		zDELETE_ARRAY(morphRefMeshVertPos);
		zDELETE_ARRAY(srcFileStats);
	}

	zBOOL LoadMMB(const zCHAR *fileName) { zSTRING s(fileName); return LoadMMB(s); }
	zBOOL LoadMMB(const zSTRING &fileName) { zCFileBIN f(fileName); return LoadMMB(f); }
	zBOOL LoadMMB(zCFileBIN &file);

	zVOID SaveMMB(const zCHAR *fileName) { zSTRING s(fileName); SaveMMB(s); }
	zVOID SaveMMB(const zSTRING &fileName) { zCFileBIN f(fileName, TRUE); SaveMMB(f); }
	zVOID SaveMMB(zCFileBIN &file);
};
