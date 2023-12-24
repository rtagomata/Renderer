#pragma once
#include "Serializer.h"
#include "PhysicsComponent.h"

class GameObject : Serializer{
public:
	//FreeMemory();
	VECTOR3D Position;
	VECTOR3D Scale;
	PhysicsComponent* physics;
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
	GameObject() {
		//null constructor
	}
	GameObject(VECTOR3D& Position) : Position(Position) {} //for camera
	void Write(std::string name) override;
	void Read(std::string name) override;
	virtual void Render()= 0;
private:
};