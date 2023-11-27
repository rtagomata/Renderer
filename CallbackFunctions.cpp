#include "CallbackFunctions.h"
#define cameraControl 0
#define playerControl 1
namespace callbackFunctions {

	GLfloat eyeX = 10.0;
	GLfloat eyeY = 1.0;
	GLfloat eyeZ = 4.0;
	GLfloat centerX = 9.0;
	GLfloat centerY = 0.0;
	GLfloat centerZ = 3.0;
	GLfloat upX = 0.0;
	GLfloat upY = 1.0;
	GLfloat upZ = 0.0;

	int previousX = 0;
	int previousY = 0;

	RoomMesh* roomMesh = nullptr;
	int currentButton = 0;
	int keyboardMode = cameraControl;
	void display(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
		glPushMatrix();
		drawRoom();
		callbackFunctions::roomMesh->DrawMesh(16);
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
		gluPerspective(60.0, (GLfloat)w / h, 0.2, 40.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
		//glduLookAt(0.0, 6.0, 22.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}

	void keyboard(unsigned char key, int x, int y) {
		if (keyboardMode == cameraControl)
		{
			VECTOR3D* refToCam = new VECTOR3D((float)centerX-eyeX, (float)centerY-eyeY, (float)centerZ-eyeZ);
			VECTOR3D* yUnitVec = new VECTOR3D(0,1.0f, 0);
			VECTOR3D* xUnitVec = new VECTOR3D(1.0f,0, 0);
			VECTOR3D u1 = refToCam->CrossProduct(*yUnitVec);
			VECTOR3D u2 = refToCam->CrossProduct(*xUnitVec);
			refToCam->Normalize();
			u1.Normalize();
			u2.Normalize();

			switch (key)
			{
			case 'w': 
				eyeZ += 0.1 * refToCam->z;
				centerZ += 0.1* refToCam->z;
				eyeY += 0.1 * refToCam->y;
				centerY += 0.1 * refToCam->y;
				eyeX += 0.1 * refToCam->x;
				centerX += 0.1 * refToCam->x;
				break;
			case 's':
				eyeZ += -0.1 * refToCam->z;
				centerZ += -0.1 * refToCam->z;
				eyeY += -0.1 * refToCam->y;
				centerY += -0.1 * refToCam->y;
				eyeX += -0.1 * refToCam->x;
				centerX += -0.1 * refToCam->x;
				break;
			case 'a':
				eyeZ += -0.1 * u1.z;
				centerZ += -0.1 * u1.z;
				eyeY += -0.1 * u1.y;
				centerY += -0.1 * u1.y;
				eyeX += -0.1 * u1.x;
				centerX += -0.1 * u1.x;
				break;
			case 'd':
				eyeZ += 0.1 * u1.z;
				centerZ += 0.1 * u1.z;
				eyeY += 0.1 * u1.y;
				centerY += 0.1 * u1.y;
				eyeX += 0.1 * u1.x;
				centerX += 0.1 * u1.x;
				break;
			case 'z':
				eyeZ += 0.1 * u2.z;
				centerZ += 0.1 * u2.z;
				eyeY += 0.1 * u2.y;
				centerY += 0.1 * u2.y;
				eyeX += 0.1 * u2.x;
				centerX += 0.1 * u2.x;
				break;
			case 'x':
				eyeZ += -0.1 * u2.z;
				centerZ += -0.1 * u2.z;
				eyeY += -0.1 * u2.y;
				centerY += -0.1 * u2.y;
				eyeX += -0.1 * u2.x;
				centerX += -0.1 * u2.x;
				break;
			}
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
			if (previousX < xMouse)
			{
				centerX -= 0.07;
			}
			else if (previousX > xMouse)
			{
				centerX += 0.07;
			}
			if (previousY < yMouse)
			{
				centerY += 0.07;
			}
			else if (previousY > yMouse)
			{
				centerY -= 0.07;
			}
		}
		previousX = xMouse;
		previousY = yMouse;
		glutPostRedisplay();   // Trigger a window redisplay
	}
}