#include "Initializer.h"

namespace Initializer {
	bool initGlut(int argc, char** argv, const int& vWidth, const int& vHeight) {
		glewExperimental = GL_TRUE;
		
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(vWidth, vHeight);
		glutInitWindowPosition(200, 30);
		glutCreateWindow("3D Room");

		GLenum err = glewInit();

		if (GLEW_OK != err)
		{
			fprintf(stderr, "Glew error: %s\n", glewGetErrorString(err));
		}
		
		return true;
	}

	std::string loadShaderSrc(const std::string& filename) {
		std::ifstream is(filename);
		if (is.is_open()) {
			std::stringstream buffer;
			buffer << is.rdbuf();
			return buffer.str();
		}
		std::cerr << "Unable to open file " << filename << std::endl;
		exit(1);
	}

	void printProgramInfoLog(GLuint obj) {
		int infoLogLength = 0;
		int returnLength = 0;
		char* infoLog;
		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0) {
			infoLog = (char*)malloc(infoLogLength);
			glGetProgramInfoLog(obj, infoLogLength, &returnLength, infoLog);
			printf("%s\n", infoLog);
			free(infoLog);
		}
	}

	bool initShaders()
	{

		glEnable(GL_DEPTH_TEST);
		GLuint vertID = 0;
		GLuint fragID = 0;
		vertID = glCreateShader(GL_VERTEX_SHADER);
		fragID = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vs = loadShaderSrc("./first.vert");
		const char* vss = vs.c_str();
		std::string fs = loadShaderSrc("./first.frag");
		const char* fss = fs.c_str();


		glShaderSource(vertID, 1, &(vss), NULL);
		glShaderSource(fragID, 1, &(fss), NULL);

		glCompileShader(vertID);
		glCompileShader(fragID);



		game::progID = glCreateProgram();
		glAttachShader(game::progID, vertID);
		glAttachShader(game::progID, fragID);

		glBindFragDataLocation(game::progID, 0, "outputPosition");
		glLinkProgram(game::progID);

		printProgramInfoLog(game::progID);

		game::vertexLoc = glGetAttribLocation(game::progID, "inputPosition");
		game::normalLoc = glGetAttribLocation(game::progID, "inputNormal");

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

		VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
		VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
		VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);
		callbackFunctions::roomMesh = new RoomMesh(16, 32.0);
		callbackFunctions::roomMesh->InitMesh(16, origin, 32.0, 32.0, dir1v, dir2v);


		VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
		VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
		VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
		float shininess = 0.2;
		callbackFunctions::roomMesh->SetMaterial(ambient, diffuse, specular, shininess);

		return true;
	}


	bool setCallbackFunctions() {
		glutDisplayFunc(callbackFunctions::display);
		glutReshapeFunc(callbackFunctions::reshape);
		glutMouseFunc(callbackFunctions::mouse);
		glutMotionFunc(callbackFunctions::mouseMotionHandler);
		glutKeyboardFunc(callbackFunctions::keyboardDown);
		glutKeyboardUpFunc(callbackFunctions::keyboardUp);
		glutSpecialFunc(callbackFunctions::functionKeys);
		return true;
	}

	bool initializeGameObjects()
	{
		//example room objects
		/*for (int i = 0; i < 100; i++)
		{
			game::gameObjects.push_back((GameObject*)new Cube({ float((i % 100) - 50) * 2, float((i % 100) % 10) * 2 ,float((i / 100) - 50) * 2}, {0.1,0.1,0.1}, 1.0, 0, 0, 0, 0));
			game::gameObjects[i]->physics.init(&(game::gameObjects[i]->Position));
			game::gameObjects[i]->physics.gravityEnabled = true;
			//game::gameObjects[i]->Write("gobj\\object" + std::to_string(i) + ".bin");
			//game::gameObjects.push_back((GameObject*) new Cube("gobj\\object" + std::to_string(i) + ".bin"));
		}
		//init */

		VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
		callbackFunctions::roomMesh = new RoomMesh(16, 32.0);
		callbackFunctions::roomMesh->InitMesh(16, origin, 32.0, 32.0);
		origin = VECTOR3D(5.0f, 5.0f, 5.0f);


		VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
		VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
		VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);


		float shininess = 0.2;
		Cube* sample = new Cube(4.0, 8.0);
		sample->InitMesh(4, origin, 8.0, 8.0, 8.0);
		sample->SetMaterial(ambient, diffuse, specular, shininess);
		game::gameObjects.push_back((GameObject*)sample);

		/*
		VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
		VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
		VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
		float shininess = 0.2;
		callbackFunctions::roomMesh->SetMaterial(ambient, diffuse, specular, shininess);
		*/
		Camera::makeCamera();
		game::gameObjects.push_back((GameObject*)Camera::camera);
		
		//make gui elements
		GUIElements::GUIElement* picbox = (GUIElements::GUIElement*)new GUIElements::PictureBox("", { Camera::camera->eye->x, Camera::camera->eye->y }, 5.0, 5.0);
		Camera::camera->GUIElements.push_back(picbox);

		return true;
	}

	bool InitializeAll(int argc, char** argv, const int& vWidth, const int& vHeight) {
		std::cout << "Initializing Glut...";
		if (Initializer::initGlut(argc, argv, vWidth, vHeight)) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return false;
		}

		std::cout << "Initializing OpenGL...";
		if (Initializer::initOpenGL()) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return false;
		}
		std::cout << "Setting callback fucntions...";
		if (Initializer::setCallbackFunctions()) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return false;
		}
		std::cout << "Initializing shaders";
		if (Initializer::initShaders())
		{
			std::cout << "OK!\n";
		}
		std::cout << "Initializing game objects...";
		if (Initializer::initializeGameObjects()) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return false;
		}
		std::cout << "Initializing game thread...";
		try {
			game::bkgdThread = std::thread(callbackFunctions::backgroundLogic);
		}
		catch (std::exception e) {
			std::cout << "FAILED!\n";
			std::cout << e.what() << "\n";
			return false;
		}
		if (game::bkgdThread.joinable()) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "FAILED!\n";
			return false;
		}

		return true;
	}
}