#pragma once
#include "Misc.h"
#include <fstream>
#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Camera.h"

namespace callbackFunctions {
	extern RoomMesh* roomMesh;
	extern int currentButton;
	extern bool firstTimeMouseMovement;
	extern bool keys[256];
	void trialMovement();
	void display(void);
	void drawRoom();
	void reshape(int w, int h);
	void keyboard(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);
	void keyboardDown(unsigned char key, int x, int y);
	void functionKeys(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouseMotionHandler(int xMouse, int yMouse);
	void calculateFPS();
}