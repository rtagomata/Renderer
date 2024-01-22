#pragma once
#include "Serializer.h"
#include "PhysicsComponent.h"
struct MeshVertex
{
	VECTOR3D	position;
	VECTOR3D    normal;
};



struct MeshQuad
{
	// pointers to vertices of each quad
	MeshVertex* vertices[4];
};

struct MeshTriangle
{
	MeshVertex vertices[3];
};

class GameObject : Serializer {
public:
	//FreeMemory();
	VECTOR3D Position;
	VECTOR3D Scale;
	PhysicsComponent physics;



	GameObject(VECTOR3D& Position, VECTOR3D& Scale, GLfloat& Size);
	GameObject(std::string name) : physics(PhysicsComponent()) {
		Read(name);
	}
	GameObject() :physics(PhysicsComponent()) {
		//null constructor
	}
	GameObject(VECTOR3D& Position) : Position(Position), physics(PhysicsComponent()) {} //for camera
	void Write(std::string name) override;
	void Read(std::string name) override;
	virtual void Render() = 0;
private:
};