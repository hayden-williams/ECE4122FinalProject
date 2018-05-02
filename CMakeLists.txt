cmake_minimum_required(VERSION 3.9)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)


find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
set(GLFW_LIBRARY /usr/local/Cellar/glfw/3.2.1/lib/libglfw.dylib)
set(SOIL_LIBRARY /usr/local/lib/libSOIL.dylib)
set(LOCAL_INCLUDE /usr/local/include)
set(SOIL_INCLUDE /usr/local/include/SOIL)
set(GLM_INCLUDE /usr/local/Cellar/glm/0.9.8.5/include)

include_directories(
        ${GLEW_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${LOCAL_INCLUDE}
        ${SOIL_INCLUDE}
        ${GLM_INCLUDE}
)

set(SOURCE_FILES graphics.cpp main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        ${GLEW_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        ${GLFW_LIBRARY}
        ${SOIL_LIBRARY}
        )