#pragma once
#include <gl/glut.h>

#include "StaticPropertyValues.h"

namespace callbackFunctions {
	void display(void);
	void drawRoom();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void functionKeys(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouseMotionHandler(int xMouse, int yMouse);
}