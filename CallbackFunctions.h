#pragma once
#include "StaticPropertyValues.h"
namespace callbackFunctions {
	extern RoomMesh* roomMesh;
	extern int currentButton;
	void display(void);
	void drawRoom();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void functionKeys(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouseMotionHandler(int xMouse, int yMouse);
}