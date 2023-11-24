#include "CallbackFunctions.h"
#include "RoomMesh.h"
#include "VECTOR3D.h"
namespace callbackFunctions {
	int currentButton;
	RoomMesh* roomMesh = NULL;
	void display(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(10.0, 8.0, 36.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glPushMatrix();
		drawRoom();
		glPopMatrix();
		glutSwapBuffers();
	}

	void drawRoom() {
		glMaterialfv(GL_FRONT, GL_AMBIENT, staticPropertyValues::room_mat_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, staticPropertyValues::room_mat_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, staticPropertyValues::room_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, staticPropertyValues::room_mat_shininess);

		glPushMatrix();
		glScalef(5.0, 5.0, 5.0);
		glutSolidCube(1.0);
		glPopMatrix();
	}

	void reshape(int w, int h) {
		// Set up viewport, projection, then change to modelview matrix mode - 
	// display function will then set up camera and do modeling transforms.
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, (GLdouble)w / h, 0.2, 40.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
		//glduLookAt(0.0, 6.0, 22.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	void keyboard(unsigned char key, int x, int y) {
		switch (key)
		{
		}
		glutPostRedisplay();   // Trigger a window redisplay
	}

	void functionKeys(int key, int x, int y) {
		switch (key)
		{



		}
		glutPostRedisplay();   // Trigger a window redisplay
	}

	void mouse(int button, int state, int x, int y) {
		currentButton = button;

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				;

			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
			{
				;
			}
			break;
		default:
			break;
		}

		glutPostRedisplay();   // Trigger a window redisplay
	}

	void mouseMotionHandler(int xMouse, int yMouse) {
		if (currentButton == GLUT_LEFT_BUTTON)
		{
			;
		}

		glutPostRedisplay();   // Trigger a window redisplay
	}
}