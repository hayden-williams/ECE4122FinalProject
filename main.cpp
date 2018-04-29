//
// Created by Rachel Clark on 4/19/18.
//

#include <zconf.h>
#include <thread>
#include <iostream>
#include "graphics.h"

bool keep_looping = true;
Visual v = Visual();

// anthill positions:
int num_anthills = 3;
float anthills[] = {
        // X   Y    Size
        0.25f, 0.80f, 0.15f,
        -0.7f, 0.03f, 0.2f,
        0.56f, -0.1f, 0.25f
};

// breadcrumb positions and sizes:
int num_breadcrumbs = 3;
float breadcrumbs[] = {
        // X  Y  Size
        0.7f, -0.3f, 0.1f,
        -0.4f, -0.3f, 0.2f,
        -0.2f, 0.0f, 0.15f
};

// circle diameter (in same order as anthills)
float circles[] = { 0.1f, 0.2f, 0.5f };


int main() {

    while(!glfwWindowShouldClose(v.getWindow()) && keep_looping) {
        v.displayGraphicsInnerLoop(num_anthills, anthills, num_breadcrumbs, breadcrumbs, circles);
    }

    v.teardown();

    return 0;
}




