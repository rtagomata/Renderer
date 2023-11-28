#pragma once
#include "VECTOR3D.h"

class GameObject {
public:
	//FreeMemory();
	VECTOR3D Position;
	VECTOR3D Size;
	VECTOR3D Scale;
	GLfloat* Ambient;
	GLfloat* Specular;
	GLfloat* Diffuse;
	GLfloat* Shininess;
	GameObject(VECTOR3D& Position, VECTOR3D& Size, VECTOR3D& Scale,
		GLfloat *Ambient, GLfloat* Specular,
		GLfloat* Diffuse, GLfloat* Shininess);
	GameObject(const char* fileName);
	bool WriteToFile(const char* fileName);
private:
};