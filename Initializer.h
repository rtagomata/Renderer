#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "Cube.h"
#include "callbackFunctions.h"

namespace Initializer {
	// Initialize GLUT

	bool initGlut(int argc, char** argv, const int& vWidth, const int& vHeight);
	
	// Set up and enable lighting
	bool initOpenGL();
	
	//Setup shaders
	bool initShaders();
	std::string loadShaderSrc(const std::string& filename);
	void printProgramInfoLog(GLuint obj);
	// Set up callback functions for glut
	bool setCallbackFunctions();

	// Initializes all
	bool InitializeAll(int argc, char** argv, const int& vWidth, const int& vHeight);

	//Initializes game objects
	bool initializeGameObjects();
}