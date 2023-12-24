#pragma once
#include "GameObject.h"

class Camera : GameObject { //singleton impl
public:
	static Camera* camera;

	VECTOR3D* eye;
	VECTOR3D* center;
	VECTOR3D* up;

	void look() {
		gluLookAt(eye->x, eye->y, eye->z, center->x + eye->x, center->y + eye->y, center->z + eye->z, up->x, up->y, up->z);
	}

	static void makeCamera(VECTOR3D* eye = new VECTOR3D(10.0, 1.0, 4.0), VECTOR3D* center = new VECTOR3D(0.0, 0.0, -1.0), VECTOR3D* up = new VECTOR3D(0.0, 1.0, 0.0));

	void Render() override {}; //not useful
private:
	Camera(VECTOR3D* eye, VECTOR3D* center, VECTOR3D* up) :
		GameObject(*eye), center(center), up(up), eye(&(GameObject::Position))
	{
	}
};

