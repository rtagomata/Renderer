#include "GameObject.h"

GameObject::GameObject(VECTOR3D& Position, VECTOR3D& Scale, GLfloat& Size) :
	Position(Position), Scale(Scale), physics(PhysicsComponent())
{
}

void GameObject::Write(std::string name) {
	dataChunks.clear();
	dataChunks.push_back({ &Position, sizeof(VECTOR3D) });
	dataChunks.push_back({ &Scale, sizeof(VECTOR3D) });
	dataChunks.push_back({ &physics, sizeof(PhysicsComponent) });
	Serialize(name);
}
void GameObject::Read(std::string name) {
	dataChunks.clear();
	//make sure none of the buffers are non allocated. - maybe write check after
	dataChunks.push_back({ &Position, sizeof(VECTOR3D) });
	dataChunks.push_back({ &Scale, sizeof(VECTOR3D) });
	dataChunks.push_back({ &physics, sizeof(PhysicsComponent) });
	Deserialize(name);
}