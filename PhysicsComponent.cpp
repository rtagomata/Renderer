#include "PhysicsComponent.h"

void PhysicsComponent::init(VECTOR3D* pos)
{
	position = pos;
	gravityAcceleration = -0.000001;
	gravityEnabled = false;
	velocity = VECTOR3D(0.0, 0.0, 0.0);
	acceleration = VECTOR3D(0.0, 0.0, 0.0);
	mass = 1;
	enabled = true;
}

void PhysicsComponent::calculate(GLfloat factor) {
	if (gravityEnabled) {
		velocity.y += gravityAcceleration * factor;
	}
	velocity += acceleration * factor;
	*position += velocity;
}

void PhysicsComponent::applyForce(VECTOR3D force) {
	acceleration += force / mass;
}