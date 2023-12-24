#include "GameObject.h"

GameObject::GameObject(VECTOR3D& Position, VECTOR3D& Scale, GLfloat& Size,
	GLfloat Ambient, GLfloat Specular,
	GLfloat Diffuse, GLfloat Shininess):
	Position(Position), Scale(Scale), Size(Size),
	Ambient(Ambient), Specular(Specular), Diffuse(Diffuse),
	Shininess(Shininess), physics(PhysicsComponent())
{
}

void GameObject::Write(std::string name) {
	dataChunks.clear();
	dataChunks.push_back({ &Position, sizeof(VECTOR3D) });
	dataChunks.push_back({ &Scale, sizeof(VECTOR3D) });
	dataChunks.push_back({ &Size, sizeof(GLfloat) });
	dataChunks.push_back({ &Ambient, sizeof(GLfloat) });
	dataChunks.push_back({ &Specular, sizeof(GLfloat) });
	dataChunks.push_back({ &Diffuse, sizeof(GLfloat) });
	dataChunks.push_back({ &Shininess, sizeof(GLfloat) });
	Serialize(name);
}
void GameObject::Read(std::string name) {
	dataChunks.clear();
	//make sure none of the buffers are non allocated. - maybe write check after
	dataChunks.push_back({ &Position, sizeof(VECTOR3D) });
	dataChunks.push_back({ &Scale, sizeof(VECTOR3D) });
	dataChunks.push_back({ &Size, sizeof(GLfloat) });
	dataChunks.push_back({ &Ambient, sizeof(GLfloat) });
	dataChunks.push_back({ &Specular, sizeof(GLfloat) });
	dataChunks.push_back({ &Diffuse, sizeof(GLfloat) });
	dataChunks.push_back({ &Shininess, sizeof(GLfloat) });
	Deserialize(name);
}