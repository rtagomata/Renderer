#include "Initializer.h"

namespace Initializer {
	bool initGlut(int argc, char** argv, const int& vWidth, const int& vHeight) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(vWidth, vHeight);
		glutInitWindowPosition(200, 30);
		glutCreateWindow("3D Room");
		return true;
	}

	bool initOpenGL() {
		glLightfv(GL_LIGHT0, GL_AMBIENT, staticPropertyValues::light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, staticPropertyValues::light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, staticPropertyValues::light_specular);
		glLightfv(GL_LIGHT1, GL_AMBIENT, staticPropertyValues::light_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, staticPropertyValues::light_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, staticPropertyValues::light_specular);

		glLightfv(GL_LIGHT0, GL_POSITION, staticPropertyValues::light_position0);
		glLightfv(GL_LIGHT1, GL_POSITION, staticPropertyValues::light_position1);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);   // This second light is currently off

		// Other OpenGL setup
		glEnable(GL_DEPTH_TEST);   // Remove hidded surfaces
		glShadeModel(GL_SMOOTH);   // Use smooth shading, makes boundaries between polygons harder to see 
		glClearColor(0.4F, 0.4F, 0.4F, 0.0F);  // Color and depth for glClear
		glClearDepth(1.0f);
		glEnable(GL_NORMALIZE);    // Renormalize normal vectors 
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Nicer perspective

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		return true;
	}

	bool setCallbackFunctions() {
		glutDisplayFunc(callbackFunctions::display);
		glutReshapeFunc(callbackFunctions::reshape);
		glutMouseFunc(callbackFunctions::mouse);
		glutMotionFunc(callbackFunctions::mouseMotionHandler);
		glutKeyboardFunc(callbackFunctions::keyboard);
		glutSpecialFunc(callbackFunctions::functionKeys);
		return true;
	}

	bool InitializeAll(int argc, char** argv, const int& vWidth, const int& vHeight) {
		std::cout << "Initializing Glut...";
		if (Initializer::initGlut(argc, argv, vWidth, vHeight)) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return 1;
		}
		std::cout << "Initializing OpenGL...";
		if (Initializer::initOpenGL()) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return 1;
		}
		std::cout << "Setting callback fucntions...";
		if (Initializer::setCallbackFunctions()) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return 1;
		}
	}
}