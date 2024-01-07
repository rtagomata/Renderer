#pragma once
#include "Misc.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Camera.h"
#include "RoomMesh.h"

namespace callbackFunctions {
	extern int frameCount;
	extern int currentTime;
	extern int previousTime;
	extern int countFPS;
	extern bool recordFPS;
	extern std::string newRecordFile;
	extern std::ofstream f;
	extern VECTOR3D refToCam;
	extern VECTOR3D yUnitVec;
	extern VECTOR3D xUnitVec;
	extern VECTOR3D nyUnitVec;
	extern VECTOR3D nxUnitVec;
	extern float yaw;
	extern float pitch;
	extern int previousX;
	extern int previousY;
	extern VECTOR3D rotateAngle;
	extern RoomMesh* roomMesh;
	extern int currentButton;
	extern bool firstTimeMouseMovement;
	extern bool keys[256];
	extern int keyboardMode;


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
	void animationHandler(int param);
	void calculateFPS();

	void backgroundLogic();
}