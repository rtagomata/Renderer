#include "Cube.h"

Cube::Cube(VECTOR3D Position, VECTOR3D Scale, GLfloat Size,
	GLfloat Ambient, GLfloat Specular,
	GLfloat Diffuse, GLfloat Shininess): GameObject(Position,Scale,Size,
		Ambient,Specular,Diffuse,Shininess) {

}

void Cube::Render() {
	glPushMatrix();
	glScalef(Scale.x,Scale.y,Scale.z);
	glTranslatef(Position.x,Position.y,Position.z);
	glutSolidCube(Size);
	glPopMatrix();
}