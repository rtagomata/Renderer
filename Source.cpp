#pragma once
#include "Initializer.h"

const int vWidth = 1040;
const int vHeight = 980;

int main(int argc, char** argv)
{	
	VECTOR3D ex = VECTOR3D(1.0,2.0,3.0);
	GameObject go(ex, ex, ex, 1.0, 2.0, 3.0, 4.0);
	go.Write("GameObjectTest.bin");
	go.Read("GameObjectTest.bin");
	std::cout << go.Position << "\n" << go.Shininess << '\n';
	Initializer::InitializeAll(argc, argv, vWidth, vHeight);
	glutMainLoop();
	return 0;
}