#pragma once
#include "Initializer.h"

const int vWidth = 1040;
const int vHeight = 980;

int main(int argc, char** argv)
{	
	if (!Initializer::InitializeAll(argc, argv, vWidth, vHeight)) {
		return 1; //change later maybe
	}
	glutMainLoop();
	return 0;
}