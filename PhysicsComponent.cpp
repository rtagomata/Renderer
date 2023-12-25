#include "PhysicsComponent.h"

void PhysicsComponent::init(VECTOR3D* pos)
{
	position = pos;
	gravityAcceleration = -0.01;
	gravityEnabled = false;
	velocity = VECTOR3D(0.0, 0.0, 0.0);
	acceleration = VECTOR3D(0.0, 0.0, 0.0);
	mass = 1;
	enabled = true;
}

void PhysicsComponent::calculate(GLfloat factor) {
	VECTOR3D deltaVelocity(0.0, 0.0, 0.0);
	if (gravityEnabled) {
		deltaVelocity.y += gravityAcceleration * factor;
	}
	deltaVelocity += acceleration * factor;
	velocity += deltaVelocity;
	*position += deltaVelocity;
}

void PhysicsComponent::applyForce(VECTOR3D force) {
	acceleration += force / mass;
}