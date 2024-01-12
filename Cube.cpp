#include "Cube.h"

Cube::Cube(VECTOR3D Position, VECTOR3D Scale, GLfloat Size, GLfloat Ambient, GLfloat Specular, GLfloat Diffuse, GLfloat Shininess): 
	GameObject(Position,Scale,Size) 
{

	
}

Cube::Cube(int maxMeshSize, float meshDim)
{
	minMeshSize = 1;
	numVertices = 0;
	vertices = NULL;
	numTris = 0;
	tris1 = NULL;
	tris2 = NULL;
	numFacesDrawn = 0;

	this->maxMeshSize = maxMeshSize < minMeshSize ? minMeshSize : maxMeshSize;
	this->meshDim = meshDim;

	CreateMemory();
	mat_ambient[0] = 0.0;
	mat_ambient[1] = 0.0;
	mat_ambient[2] = 0.0;
	mat_ambient[3] = 1.0;
	mat_specular[0] = 0.0;
	mat_specular[1] = 0.0;
	mat_specular[2] = 0.0;
	mat_specular[3] = 1.0;
	mat_diffuse[0] = 0.9;
	mat_diffuse[1] = 0.5;
	mat_diffuse[2] = 0.0;
	mat_diffuse[3] = 1.0;
	mat_shininess[0] = 0.0;

}

void Cube::SetMaterial(VECTOR3D ambient, VECTOR3D diffuse, VECTOR3D specular, double shininess)
{
	mat_ambient[0] = ambient.x;
	mat_ambient[1] = ambient.y;
	mat_ambient[2] = ambient.z;
	mat_ambient[3] = 1.0;
	mat_specular[0] = specular.x;
	mat_specular[1] = specular.y;
	mat_specular[2] = specular.z;
	mat_specular[3] = 1.0;
	mat_diffuse[0] = diffuse.x;
	mat_diffuse[1] = diffuse.y;
	mat_diffuse[2] = diffuse.z;
	mat_diffuse[3] = 1.0;
	mat_shininess[0] = shininess;
}

bool Cube::CreateMemory()
{
	vertices = new MeshVertex[(maxMeshSize + 1) * (maxMeshSize + 1) * 6];
	if (!vertices)
	{
		return false;
	}

	tris1 = new MeshTriangle[maxMeshSize * maxMeshSize * 6];
	tris2 = new MeshTriangle[maxMeshSize * maxMeshSize * 6];
	if (!tris1)
	{
		return false;
	}
	if (!tris2)
	{
		return false;
	}
	return true;
}

bool Cube::InitMesh(int meshSize, VECTOR3D origin, double meshLength, double meshWidth, double meshHeight, VECTOR3D dir1, VECTOR3D dir2)
{
	
	numVertices = (meshSize + 1) * (meshSize + 1) * 6;
	glGenVertexArrays(1, &VAO1);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "VAO CREATION ERROR" << std::endl;
	}

	glBindVertexArray(VAO1);
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &VBO2);




	m_meshSize = meshSize;
	VECTOR3D o;
	VECTOR3D o2;

	int currentVertex = 0;
	double sf1, sf2, sf3;

	VECTOR3D v1, v2, v3, v4;


	v1.x = dir1.x;
	v1.y = dir1.y;
	v1.z = dir1.z;
	
	VECTOR3D dir3 = VECTOR3D(-v1.y, v1.x, v1.z);
	sf1 = meshLength / meshSize;
	v1 *= sf1;

	v2.x = dir2.x;
	v2.y = dir2.y;
	v2.z = dir2.z;

	VECTOR3D dir4 = VECTOR3D(-v2.y, v2.x, v2.z);
	sf2 = meshWidth / meshSize;
	v2 *= sf2;

	v3.x = dir3.x;
	v3.y = dir3.y;
	v3.z = dir3.z;
	sf3 = meshHeight / meshSize;
	v3 *= sf3;

	VECTOR3D meshpt;

	numVertices = (meshSize + 1) * (meshSize + 1) * 6;

	o.Set(origin.x, origin.y, origin.z);



	for (int i = 0; i < meshSize + 1; i++)
	{
		for (int j = 0; j < meshSize + 1; j++)
		{
			meshpt.x = o.x + j * v1.x;
			meshpt.y = o.y + j * v1.y;
			meshpt.z = o.z + j * v1.z;

			vertices[currentVertex].position.Set(meshpt.x, meshpt.y, meshpt.z);

			std::cout << meshpt.x << ":" << meshpt.y << ":" << meshpt.z << std::endl;
			currentVertex++;
		}
		o += v2;
	}
	VECTOR3D origin2 = vertices[currentVertex - 1].position;

	o.Set(origin.x, origin.y, origin.z);
	std::cout << "-----------------" << std::endl;
	for (int i = 0; i < meshSize + 1; i++)
	{
		for (int j = 0; j < meshSize + 1; j++)
		{
			meshpt.x = o.x + j * v1.x;
			meshpt.y = o.y + j * v1.y;
			meshpt.z = o.z + j * v1.z;

			vertices[currentVertex].position.Set(meshpt.x, meshpt.y, meshpt.z);
			std::cout << meshpt.x << ":" << meshpt.y << ":" << meshpt.z << std::endl;
			currentVertex++;
		}
		o += v3;
	}


	o.Set(origin.x, origin.y, origin.z);
	std::cout << "-----------------" << std::endl;
	for (int i = 0; i < meshSize + 1; i++)
	{
		for (int j = 0; j < meshSize + 1; j++)
		{
			meshpt.x = o.x + j * v2.x;
			meshpt.y = o.y + j * v2.y;
			meshpt.z = o.z + j * v2.z;

			vertices[currentVertex].position.Set(meshpt.x, meshpt.y, meshpt.z);
			std::cout << meshpt.x << ":" << meshpt.y << ":" << meshpt.z << std::endl;
			currentVertex++;
		}
		o += v3;
	}

	o2.Set(origin2.x, origin2.y, origin2.z);
	std::cout << origin2.x << ":" << origin2.y << ":" << origin2.z << std::endl;
	for (int i = 0; i < meshSize + 1; i++)
	{
		for (int j = 0; j < meshSize + 1; j++)
		{
			meshpt.x = o2.x + j * -v2.x;
			meshpt.y = o2.y + j * -v2.y;
			meshpt.z = o2.z + j * -v2.z;

			vertices[currentVertex].position.Set(meshpt.x, meshpt.y, meshpt.z);

			std::cout << meshpt.x << ":" << meshpt.y << ":" << meshpt.z << std::endl;
			currentVertex++;
		}
		o2 += v3;
	}

	o2.Set(origin2.x, origin2.y, origin2.z);
	std::cout << origin2.x << ":" << origin2.y << ":" << origin2.z << std::endl;
	for (int i = 0; i < meshSize + 1; i++)
	{
		for (int j = 0; j < meshSize + 1; j++)
		{
			meshpt.x = o2.x + j * -v1.x;
			meshpt.y = o2.y + j * -v1.y;
			meshpt.z = o2.z + j * -v1.z;

			vertices[currentVertex].position.Set(meshpt.x, meshpt.y, meshpt.z);

			std::cout << meshpt.x << ":" << meshpt.y << ":" << meshpt.z << std::endl;
			currentVertex++;
		}
		o2 += v3;
	}

	VECTOR3D origin3 = vertices[(meshSize + 1) * (meshSize + 1) * 2 - meshSize - 1].position;
	o.Set(origin3.x, origin3.y, origin3.z);

	for (int i = 0; i < meshSize + 1; i++)
	{
		for (int j = 0; j < meshSize + 1; j++)
		{
			meshpt.x = o.x + j * v1.x;
			meshpt.y = o.y + j * v1.y;
			meshpt.z = o.z + j * v1.z;

			vertices[currentVertex].position.Set(meshpt.x, meshpt.y, meshpt.z);

			std::cout << meshpt.x << ":" << meshpt.y << ":" << meshpt.z << std::endl;
			currentVertex++;
		}
		o += v2;
	}






	numTris = (meshSize) * (meshSize) * 6;
	int currentTri = 0;

	int offset = (meshSize + 1) * (meshSize + 1);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < meshSize; j++)
		{
			for (int k = 0; k < meshSize; k++)
			{
				tris1[currentTri].vertices[0] = &vertices[j * (meshSize + 1) + k + offset * i];
				tris1[currentTri].vertices[1] = &vertices[j * (meshSize + 1) + k + 1 + offset * i];
				tris1[currentTri].vertices[2] = &vertices[(j + 1) * (meshSize + 1) + k + offset * i];
				tris2[currentTri].vertices[0] = &vertices[j * (meshSize + 1) + k + 1 + offset * i];
				tris2[currentTri].vertices[1] = &vertices[(j + 1) * (meshSize + 1) + k + 1 + offset * i];
				tris2[currentTri].vertices[2] = &vertices[(j + 1) * (meshSize + 1) + k + offset * i];
				currentTri++;
			}
		}
	}
	
	

	this->ComputeNormals();

	triangles = new VECTOR3D[meshSize * meshSize * 6 * 3 * 2];
	offset = meshSize * meshSize * 6 * 3;
	for (int i = 0; i < meshSize * meshSize * 6; i++)
	{
		triangles[i * 3] = tris1[i].vertices[0]->position;
		triangles[i * 3 + 1] = tris1[i].vertices[1]->position;
		triangles[i * 3 + 2] = tris1[i].vertices[2]->position;
		triangles[i * 3 + offset] = tris2[i].vertices[0]->position;
		triangles[i * 3 + 1 + offset] = tris2[i].vertices[1]->position;
		triangles[i * 3 + 2 + offset] = tris2[i].vertices[2]->position;

	}
	 


	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VECTOR3D) * meshSize * meshSize * 6 * 3 * 2, triangles, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VECTOR3D), nullptr);
	glEnableVertexAttribArray(game::vertexLoc);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VECTOR3D), nullptr);
	glEnableVertexAttribArray(game::normalLoc);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);




	return true;
}

void Cube::DrawMesh()
{
	int currentTri = 0;
	int meshSize = m_meshSize;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	/*
	for (int j = 0; j < meshSize * 6; j++)
	{
		for (int k = 0; k < meshSize; k++)
		{
			glBegin(GL_TRIANGLES);



			glNormal3f(tris1[currentTri].vertices[0]->normal.x,
				tris1[currentTri].vertices[0]->normal.y,
				tris1[currentTri].vertices[0]->normal.z);
			glVertex3f(tris1[currentTri].vertices[0]->position.x,
				tris1[currentTri].vertices[0]->position.y,
				tris1[currentTri].vertices[0]->position.z);

			glNormal3f(tris1[currentTri].vertices[1]->normal.x,
				tris1[currentTri].vertices[1]->normal.y,
				tris1[currentTri].vertices[1]->normal.z);

			glVertex3f(tris1[currentTri].vertices[1]->position.x,
				tris1[currentTri].vertices[1]->position.y,
				tris1[currentTri].vertices[1]->position.z);

			glNormal3f(tris1[currentTri].vertices[2]->normal.x,
				tris1[currentTri].vertices[2]->normal.y,
				tris1[currentTri].vertices[2]->normal.z);

			glVertex3f(tris1[currentTri].vertices[2]->position.x,
				tris1[currentTri].vertices[2]->position.y,
				tris1[currentTri].vertices[2]->position.z);


			glEnd();

			glBegin(GL_TRIANGLES);



			glNormal3f(tris2[currentTri].vertices[0]->normal.x,
				tris2[currentTri].vertices[0]->normal.y,
				tris2[currentTri].vertices[0]->normal.z);
			glVertex3f(tris2[currentTri].vertices[0]->position.x,
				tris2[currentTri].vertices[0]->position.y,
				tris2[currentTri].vertices[0]->position.z);

			glNormal3f(tris2[currentTri].vertices[1]->normal.x,
				tris2[currentTri].vertices[1]->normal.y,
				tris2[currentTri].vertices[1]->normal.z);

			glVertex3f(tris2[currentTri].vertices[1]->position.x,
				tris2[currentTri].vertices[1]->position.y,
				tris2[currentTri].vertices[1]->position.z);

			glNormal3f(tris2[currentTri].vertices[2]->normal.x,
				tris2[currentTri].vertices[2]->normal.y,
				tris2[currentTri].vertices[2]->normal.z);

			glVertex3f(tris2[currentTri].vertices[2]->position.x,
				tris2[currentTri].vertices[2]->position.y,
				tris2[currentTri].vertices[2]->position.z);


			glEnd();

			currentTri++;
		}
	}
	*/
	glUseProgram(game::progID);
	glBindVertexArray(VAO1);
	glDrawArrays(GL_TRIANGLES, 0, meshSize * meshSize * 6 * 3 * 2);
	glBindVertexArray(0);
}

void Cube::UpdateMesh()
{
}

void Cube::FreeMemory()
{
	if (vertices)
		delete[] vertices;
	vertices = NULL;
	numVertices = 0;

	if (tris1)
		delete[] tris1;
	tris1 = NULL;
	if (tris2)
		delete[] tris2;
	tris2 = NULL;

	numTris= 0;
}

void Cube::ComputeNormals()
{
	int currentTri = 0;

	for (int j = 0; j < m_meshSize; j++)
	{
		for (int k = 0; k < m_meshSize * 6; k++)
		{
			VECTOR3D n0, n1, n2, n3, e0, e1, e2, ne0, ne1, ne2;

			tris1[currentTri].vertices[0]->normal.LoadZero();
			tris1[currentTri].vertices[1]->normal.LoadZero();
			tris1[currentTri].vertices[2]->normal.LoadZero();
			e0 = tris1[currentTri].vertices[1]->position - tris1[currentTri].vertices[2]->position;
			e1 = tris1[currentTri].vertices[2]->position - tris1[currentTri].vertices[0]->position;
			e2 = tris1[currentTri].vertices[0]->position - tris1[currentTri].vertices[1]->position;
			e0.Normalize();
			e1.Normalize();
			e2.Normalize();

			n0 = e0.CrossProduct(-e2);
			n0.Normalize();
			tris1[currentTri].vertices[0]->normal += n0;

			n1 = e1.CrossProduct(-e0);
			n1.Normalize();
			tris1[currentTri].vertices[1]->normal += n1;

			n2 = e2.CrossProduct(-e1);
			n2.Normalize();
			tris1[currentTri].vertices[2]->normal += n2;


			tris1[currentTri].vertices[0]->normal.Normalize();
			tris1[currentTri].vertices[1]->normal.Normalize();
			tris1[currentTri].vertices[2]->normal.Normalize();


			tris2[currentTri].vertices[0]->normal.LoadZero();
			tris2[currentTri].vertices[1]->normal.LoadZero();
			tris2[currentTri].vertices[2]->normal.LoadZero();
			e0 = tris2[currentTri].vertices[1]->position - tris2[currentTri].vertices[2]->position;
			e1 = tris2[currentTri].vertices[2]->position - tris2[currentTri].vertices[0]->position;
			e2 = tris2[currentTri].vertices[0]->position - tris2[currentTri].vertices[1]->position;
			e0.Normalize();
			e1.Normalize();
			e2.Normalize();

			n0 = e0.CrossProduct(-e2);
			n0.Normalize();
			tris2[currentTri].vertices[0]->normal += n0;

			n1 = e1.CrossProduct(-e0);
			n1.Normalize();
			tris2[currentTri].vertices[1]->normal += n1;

			n2 = e2.CrossProduct(-e1);
			n2.Normalize();
			tris2[currentTri].vertices[2]->normal += n2;


			tris2[currentTri].vertices[0]->normal.Normalize();
			tris2[currentTri].vertices[1]->normal.Normalize();
			tris2[currentTri].vertices[2]->normal.Normalize();

			currentTri++;
		}
	}
}

void Cube::Render() {
	DrawMesh();
}
