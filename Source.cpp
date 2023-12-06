#pragma once
#include "Initializer.h"

const int vWidth = 1040;
const int vHeight = 980;

int main(int argc, char** argv)
{	
	Initializer::InitializeAll(argc, argv, vWidth, vHeight);
	glutMainLoop();
	return 0;
}