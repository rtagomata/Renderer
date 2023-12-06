#pragma once
#include "VECTOR3D.h"
#include "FileOperator.h"

class GameObject : Serializer{
public:
	//FreeMemory();
	VECTOR3D Position;
	VECTOR3D Size;
	VECTOR3D Scale;
	GLfloat Ambient;
	GLfloat Specular;
	GLfloat Diffuse;
	GLfloat Shininess;
	GameObject(VECTOR3D& Position, VECTOR3D& Size, VECTOR3D& Scale,
		GLfloat Ambient, GLfloat Specular,
		GLfloat Diffuse, GLfloat Shininess);
	GameObject(std::string name) {
		Read(name);
	}
	void Write(std::string name){
		dataChunks.clear();
		dataChunks.push_back({ &Position, sizeof(VECTOR3D) });
		dataChunks.push_back({ &Size, sizeof(VECTOR3D) });
		dataChunks.push_back({ &Scale, sizeof(VECTOR3D) });
		dataChunks.push_back({ &Ambient, sizeof(GLfloat) });
		dataChunks.push_back({ &Specular, sizeof(GLfloat) });
		dataChunks.push_back({ &Diffuse, sizeof(GLfloat) });
		dataChunks.push_back({ &Shininess, sizeof(GLfloat) });
		Serialize(name);
	}
	void Read(std::string name){
		dataChunks.clear();
		//make sure none of the buffers are non allocated. - maybe write check after
		dataChunks.push_back({ &Position, sizeof(VECTOR3D) });
		dataChunks.push_back({ &Size, sizeof(VECTOR3D) });
		dataChunks.push_back({ &Scale, sizeof(VECTOR3D) });
		dataChunks.push_back({ &Ambient, sizeof(GLfloat) });
		dataChunks.push_back({ &Specular, sizeof(GLfloat) });
		dataChunks.push_back({ &Diffuse, sizeof(GLfloat) });
		dataChunks.push_back({ &Shininess, sizeof(GLfloat) });
		Deserialize(name);
	}
private:
};