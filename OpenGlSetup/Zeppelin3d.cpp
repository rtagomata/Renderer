// This code example is created for educational purpose
// by Thorsten Thormaehlen (contact: www.thormae.de).
// It is distributed without any warranty.

#include <GL/glew.h>
#include <GL/freeglut.h> // we use glut here as window manager
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Renderer {

private:
    struct Vertex
    {
        float position[3];
        float color[4];
    };

private:
    enum { Triangle, numVAOs };
    enum { TriangleAll, numVBOs };
    GLuint vaoID[numVAOs];
    GLuint bufID[numVBOs];
    int triangleVertNo;
    GLuint progID;
    GLuint vertID;
    GLuint fragID;
    GLint vertexLoc;
    GLint colorLoc;
public:
    // constructor
    Renderer() : triangleVertNo(0), progID(0), vertID(0),
        fragID(0), vertexLoc(-1), colorLoc(-1) {}
    //destructor
    ~Renderer() {
        glDeleteVertexArrays(numVAOs, vaoID);
        glDeleteBuffers(numVBOs, bufID);
        glDeleteProgram(progID);
        glDeleteShader(vertID);
        glDeleteShader(fragID);
    }

public:
    void init() {
        glEnable(GL_DEPTH_TEST);

        setupShaders();

        // create a Vertex Array Objects (VAO)
        glGenVertexArrays(numVAOs, vaoID);

        // generate a Vertex Buffer Object (VBO)
        glGenBuffers(numVBOs, bufID);

        // binding the Triangle VAO
        glBindVertexArray(vaoID[Triangle]);

        float triangleVertexData[] = {
           0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
          -0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
           0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };
        triangleVertNo = 3;

        glBindBuffer(GL_ARRAY_BUFFER, bufID[TriangleAll]);
        glBufferData(GL_ARRAY_BUFFER, triangleVertNo * sizeof(Vertex),
            triangleVertexData, GL_STATIC_DRAW);

        int stride = sizeof(Vertex);
        char* offset = (char*)NULL;

        // position
        if (vertexLoc != -1) {
            glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, stride, offset);
            glEnableVertexAttribArray(vertexLoc);
        }

        // color
        if (colorLoc != -1) {
            offset = (char*)NULL + 3 * sizeof(float);
            glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, stride, offset);
            glEnableVertexAttribArray(colorLoc);
        }
    }

    void setupShaders() {

        // create shader
        vertID = glCreateShader(GL_VERTEX_SHADER);
        fragID = glCreateShader(GL_FRAGMENT_SHADER);

        // load shader source from file
        std::string vs = loadShaderSrc("./first.vert");
        const char* vss = vs.c_str();
        std::string fs = loadShaderSrc("./first.frag");
        const char* fss = fs.c_str();

        // specify shader source
        glShaderSource(vertID, 1, &(vss), NULL);
        glShaderSource(fragID, 1, &(fss), NULL);

        // compile the shader
        glCompileShader(vertID);
        glCompileShader(fragID);

        // check for errors
        printShaderInfoLog(vertID);
        printShaderInfoLog(fragID);

        // create program and attach shaders
        progID = glCreateProgram();
        glAttachShader(progID, vertID);
        glAttachShader(progID, fragID);

        // "outColor" is a user-provided OUT variable
        // of the fragment shader.
        // Its output is bound to the first color buffer
        // in the framebuffer
        glBindFragDataLocation(progID, 0, "outputColor");

        // link the program
        glLinkProgram(progID);
        // output error messages
        printProgramInfoLog(progID);

        // "inputPosition" and "inputColor" are user-provided
        // IN variables of the vertex shader.
        // Their locations are stored to be used later with
        // glEnableVertexAttribArray()
        vertexLoc = glGetAttribLocation(progID, "inputPosition");
        colorLoc = glGetAttribLocation(progID, "inputColor");

    }

    void resize(int w, int h) {
        glViewport(0, 0, w, h);
    }

    void display() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(progID);

        // bind Triangle VAO
        glBindVertexArray(vaoID[Triangle]);
        // render data
        glDrawArrays(GL_TRIANGLES, 0, triangleVertNo);
    }
private:
    void printShaderInfoLog(GLuint obj) {
        int infoLogLength = 0;
        int returnLength = 0;
        char* infoLog;
        glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            infoLog = (char*)malloc(infoLogLength);
            glGetShaderInfoLog(obj, infoLogLength, &returnLength, infoLog);
            printf("%s\n", infoLog);
            free(infoLog);
        }
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

    std::string loadShaderSrc(const std::string& filename) {
        std::ifstream is(filename);
        if (is.is_open()) {
            std::stringstream buffer;
            buffer << is.rdbuf();
            return buffer.str();
        }
        cerr << "Unable to open file " << filename << endl;
        exit(1);
    }
};


//this is a static pointer to a Renderer used in the glut callback functions
static Renderer* renderer;

//glut static callbacks start
static void glutResize(int w, int h)
{
    renderer->resize(w, h);
}

static void glutDisplay()
{
    renderer->display();
    glutSwapBuffers();
    glutReportErrors();
}

static void timer(int v)
{
    float offset = 1.0f;
    glutDisplay();
    glutTimerFunc(unsigned(20), timer, ++v);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);

    glutCreateWindow("First Shader Example");
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Glew error: %s\n", glewGetErrorString(err));
    }
    glutDisplayFunc(glutDisplay);
    //glutIdleFunc(glutDisplay);
    glutReshapeFunc(glutResize);

    renderer = new Renderer;
    renderer->init();

    glutTimerFunc(unsigned(20), timer, 0);

    glutMainLoop();
}