#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <SOIL/SOIL.h>
#include <thread>
#include "graphics.h"

const int ANTHILL_TEX = 0;
const int BREADCRUMB_TEX = 1;
const int NO_TEX = 2;

Visual::Visual(int width, int height) {

    window = initialize(width, height, "Ant Colony Simulator - ECE 4122 Final Project");

    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex Buffer Object
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // activate as array buffer

    shaderProgram = createProgram();
    setAttrib(shaderProgram, posSize, colSize, texSize);

    // load texture
    glGenTextures(1, &tex);
    loadTexture(shaderProgram, tex, "../texture.jpg", "tex", 0);

    // enable blending for transparency
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniform1i(glGetUniformLocation(shaderProgram, "width"), width);
    glUniform1i(glGetUniformLocation(shaderProgram, "height"), height);

    GLint m_viewport[4];
    glGetIntegerv( GL_VIEWPORT, m_viewport );
    std::cout << "viewport x: " << m_viewport[2] << " viewport y: " << m_viewport[3] << std::endl;

    glUniform1i(glGetUniformLocation(shaderProgram, "viewportx"), m_viewport[2]);
    glUniform1i(glGetUniformLocation(shaderProgram, "viewporty"), m_viewport[3]);

}

void Visual::createSquare(GLfloat* vertices, float side_length, float x, float y, int tex) {
    // vertices for white square centered at origin
    GLfloat r = 1.0f;
    GLfloat g = 1.0f;
    GLfloat b = 1.0f;

    float a = side_length/2.0f;

    float texcoords[4] = {0.0f};
    float temp1[] = {0.0f, 0.0f, 0.5f, 1.0f};
    float temp2[] = {0.5f, 0.0f, 1.0f, 1.0f};
    float temp3[] = {0.0f, 0.0f, 0.0f, 0.0f};
    switch (tex) {
        case ANTHILL_TEX:
            std::copy(temp1, temp1 + 4, texcoords);
            break;
        case BREADCRUMB_TEX:
            std::copy(temp2, temp2 + 4, texcoords);
            break;
        case NO_TEX:
            std::copy(temp3, temp3 + 4, texcoords);
            break;
    }

    GLfloat temp[] {
        // X Y R  G  B
        -a + x, a + y, r, g, b, texcoords[0], texcoords[1], // top left
        a + x, a + y, r, g, b, texcoords[2], texcoords[1], // top right
        a + x, -a + y, r, g, b, texcoords[2], texcoords[3], // bottom right
        a + x, -a + y, r, g, b, texcoords[2], texcoords[3], // bottom right
        -a + x, -a + y, r, g, b, texcoords[0], texcoords[3], // bottom left
        -a + x, a + y, r, g, b, texcoords[0], texcoords[1] // top left
    };

    std::copy(temp, temp + totalSize * 6, vertices);
}


// place inside while(!glfwWindowShouldClose(window)) loop
void Visual::displayGraphicsInnerLoop(int num_anthills, float anthills[], int num_breadcrumbs, float breadcrumbs[], float circles[], float lines[]) {

    GLfloat my_vert[totalSize * 6 * (num_anthills + num_breadcrumbs + num_anthills + num_anthills)];

    // create vertices to represent anthills
    for (int i = 0; i < num_anthills; i++) {
        createSquare(my_vert + i * totalSize * 6, anthills[3*i + 2],
                     anthills[3*i], anthills[3*i + 1], ANTHILL_TEX);
    }
    // create vertices for breadcrumbs
    for (int i = 0; i < num_breadcrumbs; i++) {
        createSquare(my_vert + (i + num_anthills) * totalSize * 6, breadcrumbs[3*i + 2],
                     breadcrumbs[3*i], breadcrumbs[3*i + 1], BREADCRUMB_TEX);
    }
    // create squares for the expanding circles
    for (int i = 0; i < num_anthills; i++) {
        createSquare(my_vert + (i + num_anthills + num_breadcrumbs) * totalSize * 6,
                     circles[i], anthills[3*i], anthills[3*i + 1], NO_TEX);
    }
    // create squares to cover entire board for lines
    for (int i = 0; i < num_anthills; i++) {
        createSquare(my_vert + (i + num_anthills + num_breadcrumbs + num_anthills) * totalSize * 6,
                     2.0f, 0.0f, 0.0f, NO_TEX);
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(my_vert),
                 my_vert, GL_STATIC_DRAW); // copy data to buffer

    // Clear the screen to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw anthills and breadcrumbs
    glUniform1i(glGetUniformLocation(shaderProgram, "shape_type"), SHAPE_TYPE_TEX);
    glDrawArrays(GL_TRIANGLES, 0, 6 * (num_anthills + num_breadcrumbs));
    // draw circles
    glUniform1i(glGetUniformLocation(shaderProgram, "shape_type"), SHAPE_TYPE_CIRCLE);
    for (int i = 0; i < num_anthills; i++) {
        glUniform2f(glGetUniformLocation(shaderProgram, "center"), anthills[3*i], anthills[3*i+1]);
        glUniform1f(glGetUniformLocation(shaderProgram, "radius"), circles[i]/1000.0f);
        glDrawArrays(GL_TRIANGLES, 6 * (num_anthills + num_breadcrumbs + i), 6);
    }
    // draw lines
    glUniform1i(glGetUniformLocation(shaderProgram, "shape_type"), SHAPE_TYPE_LINE);
    for (int i = 0; i < num_anthills; i++) {
        float startx = anthills[3*i];
        float starty = anthills[3*i+1];
        glUniform2f(glGetUniformLocation(shaderProgram, "start"), startx, starty);
        float endx = breadcrumbs[3*(int(lines[2*i]))];
        float endy = breadcrumbs[3*(int(lines[2*i])) + 1];
        glUniform2f(glGetUniformLocation(shaderProgram, "end"), endx, endy);
        glUniform1f(glGetUniformLocation(shaderProgram, "distance"), lines[2*i + 1]/1000.0f);
        glDrawArrays(GL_TRIANGLES, 6 * (num_anthills + num_breadcrumbs + num_anthills + i), 6);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}


int Visual::teardown() {
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}




GLFWwindow* initialize(int width, int height, std::string title) {
    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    // GLEW initialization
    glewExperimental = GL_TRUE;
    glewInit();

    return window;
}

GLuint createProgram() {
    // read in, load, and compile vertex shader
    std::ifstream in("../vertex.glsl");
    std::string contents((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());
    const char* vertexSource = contents.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // read in, load, and compile fragment shader
    in = std::ifstream("../fragment.glsl");
    contents = std::string((std::istreambuf_iterator<char>(in)),
                           std::istreambuf_iterator<char>());
    const char* fragmentSource = contents.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // check compilation
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, nullptr, buffer);
    if (status != GL_TRUE) {
        std::cout << "Problem with vertex shader compilation: ";
        std::cout << buffer << std::endl;
        return 1;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(fragmentShader, 512, nullptr, buffer);
    if (status != GL_TRUE) {
        std::cout << "Problem with fragment shader compilation: ";
        std::cout << buffer << std::endl;
        return 1;
    }

    // create program from shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor"); // this is not needed since 1 output
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    return shaderProgram;
}

void setAttrib(GLuint shaderProgram, int posSize, int colSize, int texSize) {
    int totalSize = posSize + colSize + texSize;

    // specify and enable attributes in array
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // input, # vals, type, normalize?, stride (# between), offset
    glVertexAttribPointer(posAttrib, posSize, GL_FLOAT, GL_FALSE, totalSize*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(colAttrib, colSize, GL_FLOAT, GL_FALSE, totalSize*sizeof(float),
                          (void*)(posSize*sizeof(float)));
    glEnableVertexAttribArray(colAttrib);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glVertexAttribPointer(texAttrib, texSize, GL_FLOAT, GL_FALSE, totalSize*sizeof(float),
                          (void*)((posSize + colSize)*sizeof(float)));
    glEnableVertexAttribArray(texAttrib);
}

void setAttrib(GLuint shaderProgram, int posSize, int colSize) {
    int totalSize = posSize + colSize;

    // specify and enable attributes in array
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // input, # vals, type, normalize?, stride (# between), offset
    glVertexAttribPointer(posAttrib, posSize, GL_FLOAT, GL_FALSE, totalSize*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(colAttrib, colSize, GL_FLOAT, GL_FALSE, totalSize*sizeof(float),
                          (void*)(posSize*sizeof(float)));
    glEnableVertexAttribArray(colAttrib);
}

void loadTexture(GLuint shaderProgram, GLuint tex, std::string filename, std::string uniformname, int texnum) {
    // load image with SOIL
    int width, height;
    unsigned char* image;

    GLuint texconst;

    switch(texnum) {
        case 0:
            texconst = GL_TEXTURE0;
            break;
        case 1:
            texconst = GL_TEXTURE1;
            break;
        case 2:
            texconst = GL_TEXTURE2;
            break;
    }

    glActiveTexture(texconst);
    glBindTexture(GL_TEXTURE_2D, tex);
    image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(glGetUniformLocation(shaderProgram, uniformname.c_str()), texnum);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}





