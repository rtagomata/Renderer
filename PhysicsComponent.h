#pragma once
#include "VECTOR3D.h"

class PhysicsComponent {
public:
	bool enabled;
	VECTOR3D* position;
	GLfloat gravityAcceleration; //change to 3dvec?
	bool gravityEnabled;
	VECTOR3D velocity;
	VECTOR3D acceleration;
	GLfloat mass;

	void init(VECTOR3D* pos);
	void calculate(GLfloat factor);
	void applyForce(VECTOR3D force);
};