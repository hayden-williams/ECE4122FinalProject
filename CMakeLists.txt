cmake_minimum_required(VERSION 3.9)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES graphics.cpp main.cpp AntPile.cpp Bread.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}:/usr/local/Cellar)

MESSAGE(STATUS "module path:    " ${CMAKE_MODULE_PATH})
MESSAGE(STATUS "prefix path:    " ${CMAKE_PREFIX_PATH})
MESSAGE(STATUS "install prefix:    " ${CMAKE_INSTALL_PREFIX})

## Should automatically find GLEW ##
find_package(GLEW)
if (GLEW_FOUND)
    MESSAGE(STATUS "found GLEW")
    include_directories(${GLEW_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)

## Should automatically find OpenGL ##
find_package(OpenGL)
if (OpenGL_FOUND)
    MESSAGE(STATUS "found OpenGL")
    include_directories(${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} ${OPENGL_LIBRARIES} ${OPENGL_gl_LIBRARY} ${OPENGL_opengl_LIBRARY} ${OPENGL_glx_LIBRARY})
endif (OpenGL_FOUND)

## I have had problems having find_package() find GLFW successfully ##
find_package(GLFW)
if (GLFW_FOUND)
    MESSAGE(STATUS "found GLFW")
    include_directories(${GLFW_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY} ${GLFW_LIBRARIES})
else (GLFW_FOUND)
    ########################################################
    ##### SET BELOW VARIABLE TO GLFW LIBRARY LOCATION ######
    ########################################################
    set(GLFW_LIBRARY /usr/local/Cellar/glfw/3.2.1/lib/libglfw.dylib)
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})
endif (GLFW_FOUND)

## I have had problems having find_package() find SOIL successfully ##
find_package(SOIL)
if (SOIL_FOUND)
    MESSAGE(STATUS "found SOIL")
    include_directories(${SOIL_INCLUDE_DIR} ${SOIL_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SOIL_LIBRARY} ${SOIL_LIBRARIES})
else (SOIL_FOUND)
    #####################################################################
    ##### SET BELOW VARIABLES TO SOIL LIBRARY AND SOURCE LOCATIONS ######
    #####################################################################
    set(SOIL_LIBRARY /usr/local/lib/libSOIL.dylib)
    set(SOIL_INCLUDE /usr/local/include/SOIL)
    include_directories(${SOIL_INCLUDE})
    target_link_libraries(${PROJECT_NAME} ${SOIL_LIBRARY})
endif (SOIL_FOUND)


