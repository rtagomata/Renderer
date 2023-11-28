#include "GameObject.h"

GameObject::GameObject(VECTOR3D& Position, VECTOR3D& Size, VECTOR3D& Scale,
	GLfloat *Ambient, GLfloat* Specular,
	GLfloat *Diffuse, GLfloat* Shininess):
	Position(Position), Size(Size), Scale(Scale),
	Ambient(Ambient), Specular(Specular), Diffuse(Diffuse),
	Shininess(Shininess)
{
}
