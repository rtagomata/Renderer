#pragma once
#include <iostream>

#include "callbackFunctions.h"

namespace Initializer {
	// Initialize GLUT
	bool initGlut(int argc, char** argv, const int& vWidth, const int& vHeight);
	
	// Set up and enable lighting
	bool initOpenGL();
	
	// Set up callback functions for glut
	bool setCallbackFunctions();

	// Initializes all
	bool InitializeAll(int argc, char** argv, const int& vWidth, const int& vHeight);
}