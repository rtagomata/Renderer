#pragma once
#include "GameObject.h"
#include "Misc.h"



class Cube : GameObject {
public:

	GLfloat mat_ambient[4];
	GLfloat mat_specular[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_shininess[1];

	int m_meshSize;
	int maxMeshSize;
	int minMeshSize;
	float meshDim;

	GLuint VAO1;
	GLuint VBO1;
	GLuint VAO2;
	GLuint VBO2;


	int numVertices;
	MeshVertex* vertices;

	int numTris;
	MeshTriangle* tris1;
	MeshTriangle* tris2;
		
	VECTOR3D* triangles;

	int numFacesDrawn;

	bool CreateMemory();
	void FreeMemory();

	typedef std::pair<int, int> MaxMeshDim;

	Cube(int maxMeshSize = 40, float meshDim = 1.0f);

	~Cube()
	{
		FreeMemory();
	}

	MaxMeshDim GetMaxMeshDimensions()
	{
		return MaxMeshDim(minMeshSize, maxMeshSize);


	}

	bool InitMesh(int meshSize, VECTOR3D origin, double meshLength, double meshWidth, double meshHeight, VECTOR3D dir1 = VECTOR3D(1.0f, 0.0f, 0.0f), VECTOR3D dir2 = VECTOR3D(0.0f, 0.0f, -1.0f));
	void DrawMesh();
	void UpdateMesh();
	void SetMaterial(VECTOR3D ambient, VECTOR3D diffuse, VECTOR3D specular, double shininess);
	void ComputeNormals();


	Cube(VECTOR3D Position, VECTOR3D Scale, GLfloat Size,
		GLfloat Ambient, GLfloat Specular,
		GLfloat Diffuse, GLfloat Shininess);
	Cube(std::string name) {
		Read(name);
	}
	void Render() override;

};