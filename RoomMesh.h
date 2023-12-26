#pragma once
#include "GameObject.h"


class RoomMesh
{
private:

	int maxMeshSize;
	int minMeshSize;
	float meshDim;

	int numVertices;
	MeshVertex* vertices;

	int numQuads;
	MeshQuad* quads;

	int numFacesDrawn;

	GLfloat mat_ambient[4];
	GLfloat mat_specular[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_shininess[1];


private:
	bool CreateMemory();
	void FreeMemory();

public:

	typedef std::pair<int, int> MaxMeshDim;

	RoomMesh(int maxMeshSize = 40, float meshDim = 1.0f);

	~RoomMesh()
	{
		FreeMemory();
	}

	MaxMeshDim GetMaxMeshDimentions()
	{
		return MaxMeshDim(minMeshSize, maxMeshSize);
	}

	bool InitMesh(int meshSize, VECTOR3D origin, double meshLength, double meshWidth, VECTOR3D dir1 = VECTOR3D(1.0f, 0.0f, 0.0f), VECTOR3D dir2 = VECTOR3D(0.0f, 0.0f, -1.0f));
	void DrawMesh(int meshSize);
	void UpdateMesh();
	void SetMaterial(VECTOR3D ambient, VECTOR3D diffuse, VECTOR3D specular, double shininess);
	void ComputeNormals();


};
