#include "CallbackFunctions.h"

#define cameraControl 0
#define playerControl 1
namespace callbackFunctions {
	int frameCount; 
	int currentTime;
	int previousTime;
	int countFPS;
	bool recordFPS = false;
	std::string newRecordFile;
	std::ofstream f;

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
		Camera::camera->look();
		Camera::camera->Render();
		glPushMatrix();
		drawRoom();
		callbackFunctions::roomMesh->DrawMesh(16);
		glPopMatrix();
		glutSwapBuffers();
		trialMovement();
		calculateFPS();
		glutTimerFunc(10, animationHandler, 0);
	}

	void drawRoom() {
		glMaterialfv(GL_FRONT, GL_AMBIENT, staticPropertyValues::room_mat_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, staticPropertyValues::room_mat_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, staticPropertyValues::room_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, staticPropertyValues::room_mat_shininess);
		for (GameObject* obj : game::gameObjects) {
			obj->Render();
		}
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
		switch (key)
		{
		case '1':
			if (!recordFPS)
			{
				auto t = std::time(nullptr);
				std::tm tm;

				localtime_s(&tm, &t);

				std::stringstream filenameStream;
				filenameStream << "Records/" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ".csv";
				newRecordFile = filenameStream.str();
				f.open(newRecordFile, std::ios::app);
				f << "FPS" << std::endl;
				recordFPS = true;

			}
			break;
		case '2':
			if (recordFPS)
			{
				f.close();
				recordFPS = false;
			}
			break;
		}

		trialMovement();
	}
	void calculateFPS() {
		frameCount++;
		currentTime = glutGet(GLUT_ELAPSED_TIME);
		int timeInterval = currentTime - previousTime;
		
		if (timeInterval > 1000) {

			float fps = frameCount / (timeInterval / 1000.0f);

			previousTime = currentTime;
			if (recordFPS)
			{
				f << fps << std::endl;
				std::cout << "FPS: " << fps << std::endl;
			}
			frameCount = 0;
		}
	}
	void backgroundLogic()
	{
		int cTime;
		game::previousTime = glutGet(GLUT_ELAPSED_TIME);
		while (game::running) {
			cTime = glutGet(GLUT_ELAPSED_TIME);
			GLfloat factor = (GLfloat)(cTime - game::previousTime) / (GLfloat)1000;
			for (int i = 0; i < game::gameObjects.size(); i++) {
				if (game::gameObjects[i]->physics.enabled) {
					game::gameObjects[i]->physics.calculate(factor);
				}
			}
			game::previousTime = cTime;
		}
	}
	void trialMovement() {
		if (!keys['w'] && !keys['a'] && !keys['s'] && !keys['d'] && !keys['z'] && !keys['x']) {
			return;
		}
		refToCam = *Camera::camera->center;
		VECTOR3D u1 = refToCam.CrossProduct(yUnitVec);
		VECTOR3D u2 = refToCam.CrossProduct(u1);
		refToCam.Normalize();
		refToCam *= 0.05;
		u1.Normalize();
		u1 *= 0.05;
		u2.Normalize();
		u2 *= 0.05;
		if (keys['w']) {
			*Camera::camera->eye += refToCam;
		}
		if (keys['s']) {
			*Camera::camera->eye -= refToCam;
		}
		if (keys['a']) {
			*Camera::camera->eye -= u1;
		}
		if (keys['d']) {
			*Camera::camera->eye += u1;
		}
		if (keys['z']) {
			*Camera::camera->eye += u2;
		}
		if (keys['x']) {
			*Camera::camera->eye -= u2;
		}
		std::cout << "X: " << Camera::camera->eye->x << "   Z: " << Camera::camera->eye->z << std::endl;
		glutPostRedisplay();   // Trigger a window redisplay
	}

	void keyboard(unsigned char key, int x, int y) {
		if (keyboardMode == cameraControl)
		{
			refToCam = *Camera::camera->center - *Camera::camera->eye;
			VECTOR3D u1 = refToCam.CrossProduct(yUnitVec);
			VECTOR3D u2 = refToCam.CrossProduct(u1);
			refToCam.Normalize();
			
			u1.Normalize();
			u2.Normalize();

			switch (key)
			{
			case 'w': 
				*Camera::camera->eye += refToCam;
				break;
			case 's':
				*Camera::camera->eye -= refToCam;
				break;
			case 'a':
				*Camera::camera->eye -= u1;
				break;
			case 'd':
				*Camera::camera->eye += u1;
				break;
			case 'z':
				*Camera::camera->eye += u2;
				break;
			case 'x':
				*Camera::camera->eye -= u2;
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

	void animationHandler(int param)
	{
		glutPostRedisplay();
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
			rotateAngle.Normalize();
			*Camera::camera->center = rotateAngle;
		}
		previousX = xMouse;
		previousY = yMouse;
		glutPostRedisplay();   // Trigger a window redisplay
	}
}