#include "CallbackFunctions.h"
#define cameraControl 0
#define playerControl 1
namespace callbackFunctions {

	VECTOR3D eye = VECTOR3D(10.0, 1.0, 4.0);
	GLfloat eyeX = 10.0;
	GLfloat eyeY = 1.0;
	GLfloat eyeZ = 4.0;
	VECTOR3D center = VECTOR3D(0.0, 0.0, -1.0);
	GLfloat centerX = 9.0;
	GLfloat centerY = 0.0;
	GLfloat centerZ = 3.0;

	GLfloat upX = 0.0;
	GLfloat upY = 1.0;
	GLfloat upZ = 0.0;
	VECTOR3D refToCam;
	VECTOR3D yUnitVec = VECTOR3D(0.0, 1.0, 0.0);
	VECTOR3D xUnitVec = VECTOR3D(1.0, 0.0, 0.0);
	VECTOR3D nyUnitVec = VECTOR3D(0.0, -1.0, 0.0);
	VECTOR3D nxUnitVec = VECTOR3D(-1.0, 0.0, 0.0);

	float yaw = 0.0;
	float pitch = 0.0;

	int previousX = 0;
	int previousY = 0;

	VECTOR3D rotateAngle = VECTOR3D(0.0, 0.0, 0.0);
	RoomMesh* roomMesh = nullptr;
	int currentButton = 0;
	bool firstTimeMouseMovement = true;
	bool keys[256];
	int keyboardMode = cameraControl;
	void display(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(eye.x, eye.y, eye.z, center.x + eye.x, center.y + eye.y, center.z + eye.z, upX, upY, upZ);
		glRotatef(1.0, rotateAngle.x, rotateAngle.y, rotateAngle.z);
		glPushMatrix();
		drawRoom();
		callbackFunctions::roomMesh->DrawMesh(16);
		glPopMatrix();
		glutSwapBuffers();
		trialMovement();
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

	void keyboardUp(unsigned char key, int x, int y) {
		keys[key] = false;
	}
	void keyboardDown(unsigned char key, int x, int y) { 
		keys[key] = true;
		trialMovement();
	}

	void trialMovement() {
		if (!keys['w'] && !keys['a'] && !keys['s'] && !keys['d'] && !keys['z'] && !keys['x']) {
			return;
		}
		refToCam = center - eye;
		VECTOR3D u1 = refToCam.CrossProduct(yUnitVec);
		VECTOR3D u2 = refToCam.CrossProduct(u1);
		refToCam.Normalize();
		refToCam *= 0.1;
		u1.Normalize();
		u2.Normalize();
		if (keys['w']) {
			eye += refToCam;
		}
		if (keys['s']) {
			eye -= refToCam;
		}
		if (keys['a']) {
			eye -= u1;
		}
		if (keys['d']) {
			eye += u1;
		}
		if (keys['z']) {
			eye += u2;
		}
		if (keys['x']) {
			eye -= u2;
		}

		/*
		switch (key)
		{
		case 'w':
			eyeZ += 0.1 * refToCam->z;
			centerZ += 0.1 * refToCam->z;
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
	}*/
		glutPostRedisplay();   // Trigger a window redisplay
	}

	void keyboard(unsigned char key, int x, int y) {
		if (keyboardMode == cameraControl)
		{
			refToCam = center - eye;
			VECTOR3D u1 = refToCam.CrossProduct(yUnitVec);
			VECTOR3D u2 = refToCam.CrossProduct(u1);
			refToCam.Normalize();
			
			u1.Normalize();
			u2.Normalize();

			switch (key)
			{
			case 'w': 
				eye += refToCam;
				center += refToCam;
				break;
			case 's':
				eye -= refToCam;
				center -= refToCam;
				break;
			case 'a':
				eye -= u1;
				center -= u1;
				break;
			case 'd':
				eye += u1;
				center += u1;
				break;
			case 'z':
				eye += u2;
				center += u2;
				break;
			case 'x':
				eye -= u2;
				center -= u2;
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
		previousX = x;
		previousY = y;
		glutPostRedisplay();   // Trigger a window redisplay
	}

	void mouseMotionHandler(int xMouse, int yMouse) {
		if (currentButton == GLUT_LEFT_BUTTON)
		{
			if (firstTimeMouseMovement) {
				previousX = xMouse;
				previousY = yMouse;
				firstTimeMouseMovement = false;
				return;
			}
			float xoffset = (previousX - xMouse) * 0.01;
			float yoffset = (yMouse - previousY) * 0.01;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			rotateAngle.x = cos(yaw) * cos(pitch);
			rotateAngle.y = sin(pitch);
			rotateAngle.z = sin(yaw) * cos(pitch);
			center = rotateAngle;
		}
		previousX = xMouse;
		previousY = yMouse;
		glutPostRedisplay();   // Trigger a window redisplay
	}
}