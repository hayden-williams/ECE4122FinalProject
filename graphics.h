#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Visual {

private:

    const int posSize = 2;
    const int colSize = 3;
    const int texSize = 2;
    const int totalSize = posSize + colSize + texSize;

    const int SHAPE_TYPE_TEX = 0;
    const int SHAPE_TYPE_CIRCLE = 1;
    const int SHAPE_TYPE_LINE = 2;

    GLFWwindow* window;
    GLuint vao;
    GLuint vbo;
    GLuint shaderProgram;
    GLuint tex;

    void createSquare(GLfloat* vertices, float side_length, float x, float y, int tex);

public:

    Visual(int width, int height);
    Visual() : Visual(800, 800) {};

    void displayGraphicsInnerLoop(int num_anthills, float anthills[],
                                  int num_breadcrumbs, float breadcrumbs[], float circles[], float lines[]);
    int teardown();

    GLFWwindow* getWindow() {
        return window;
    }

};

GLFWwindow* initialize(int width, int height, std::string title);
GLuint createProgram();
void setAttrib(GLuint shaderProgram, int posSize, int colSize, int texSize);
void setAttrib(GLuint shaderProgram, int posSize, int colSize);
void loadTexture(GLuint shaderProgram, GLuint tex, std::string filename,
                 std::string uniformname, int texnum);


