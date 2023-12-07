#pragma once
#include "GameObject.h"

class Cube : GameObject{
public:
	Cube(VECTOR3D Position, VECTOR3D Scale, GLfloat Size,
		GLfloat Ambient, GLfloat Specular,
		GLfloat Diffuse, GLfloat Shininess);

	void Render() override;
};