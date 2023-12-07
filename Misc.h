#pragma once

#include "RoomMesh.h"

namespace staticPropertyValues {
	static GLfloat room_mat_ambient[] = { 0.0f,0.0f,0.0f,1.0f };
	static GLfloat room_mat_specular[] = { 0.45f,0.55f,0.45f,1.0f };
	static GLfloat room_mat_diffuse[] = { 0.1f,0.35f,0.1f,1.0f };
	static GLfloat room_mat_shininess[] = { 32.0F };

	// Light properties
	static GLfloat light_position0[] = { -4.0F, 8.0F, 8.0F, 1.0F };
	static GLfloat light_position1[] = { 4.0F, 8.0F, 8.0F, 1.0F };
	static GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	static GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	static GLfloat light_ambient[] = { 0.2F, 0.2F, 0.2F, 1.0F };
}

namespace game {
	extern std::vector<GameObject*> gameObjects;
}
