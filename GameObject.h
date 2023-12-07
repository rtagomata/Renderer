#pragma once
#include "VECTOR3D.h"
#include "Serializer.h"

class GameObject : Serializer{
public:
	//FreeMemory();
	VECTOR3D Position;
	VECTOR3D Scale;
	GLfloat Size;
	GLfloat Ambient;
	GLfloat Specular;
	GLfloat Diffuse;
	GLfloat Shininess;
	GameObject(VECTOR3D& Position, VECTOR3D& Scale, GLfloat& Size,
		GLfloat Ambient, GLfloat Specular,
		GLfloat Diffuse, GLfloat Shininess);
	GameObject(std::string name) {
		Read(name);
	}
	void Write(std::string name) override;
	void Read(std::string name) override;
	virtual void Render()= 0;
private:
};