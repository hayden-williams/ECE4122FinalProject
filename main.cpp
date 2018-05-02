// Author Stephen Williams
// Created 1 May 2018
// Edited 2 May 2018

#include <iostream>
#include "stdint.h"
#include <cmath>
#include <string>
#include <zconf.h>
#include <thread>
#include <iostream>
#include "graphics.h"

// Num of Anthills: 2-4
// Num of Crumbs: 1-4
// The play field is in +ve x,y-axis locations

uint64_t timeTick = 0; // milliseconds
uint16_t x_axis_max = 2000; // millimeters
uint16_t y_axis_max = 2000; // millimeters
uint16_t min_dist_anthills = 50; // mm
uint16_t min_dist_crumbs = 50; // mm
int num_anthill_max = 4;
int num_crumb_max = 4;
int numAnthill = 0;
int numCrumb = 0;
bool runSim = true;
uint16_t anthill_x_pos[] = { 0, 0, 0, 0 }; // x position of anthill
uint16_t anthill_y_pos[] = { 0, 0, 0, 0 }; // y position of anthill
uint16_t crumb_x_pos[] = { 0, 0, 0, 0 }; // x position of crumb
uint16_t crumb_y_pos[] = { 0, 0, 0, 0 }; // y position of crumb

// dist for anthills
double dist0_1 = 0; // dist b/t anthill[0] and anthill[1]
double dist0_2 = 0;
double dist0_3 = 0;
double dist1_2 = 0;
double dist1_3 = 0;
double dist2_3 = 0;

// dist for crumbs
double dist0c_0a = 0; // dist b/t crumb[0] and anthill[0]

int cont; //used input to pause cmd line output
std::string userInput;
int count = 0;



int main() {

	// give user choice = easier to test too
	std::cout << "Entered Main" << std::endl;
	std::cout << "Would you like to choose the number of anthills and crumbs? <y/n>" << std::endl;
	std::cin >> userInput;
	std::cout << std::endl;

	/*
	while (count < cont) {
		// change the random # generator
		rand();
		count += 1;
	}*/

	// Pick random values here
	// Create Anthill and Crumb objects

	if (!userInput.compare("y")) {
		std::cout << "How many anthills? <Pick 2-4> ";
		std::cin >> numAnthill;
		std::cout << std::endl;
		if (numAnthill < 2) {
			numAnthill = 2;
		}
		else if (numAnthill > 4) {
			numAnthill = numAnthill % num_anthill_max + 1;
			if (numAnthill == 1) numAnthill += 1;
		}

		std::wcout << "How many crumbs? <Pick 1-4> ";
		std::cin >> numCrumb;
		std::cout << std::endl;
		if (numCrumb < 1) {
			numCrumb = 1;
		}
		else if (numCrumb > 4) {
			numCrumb = numCrumb % num_crumb_max + 1;
			if (numCrumb == 0) numCrumb += 1;
		}
	}
	else {
		numAnthill = rand() % num_anthill_max + 1;
		if (numAnthill == 1) numAnthill += 1;
		std::cout << "Num of Anthill is " << numAnthill << std::endl;

		numCrumb = rand() % num_crumb_max + 1;
		if (numCrumb == 1) numCrumb += 1;
		std::cout << "Num of Crumb is " << numCrumb << std::endl;
	}
	
	// Randomly pick anthill
	if (numAnthill == 2) {
		// 2 Anthills
		anthill_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		anthill_y_pos[0] = rand() % y_axis_max;
		anthill_x_pos[1] = rand() % x_axis_max;
		anthill_y_pos[1] = rand() % y_axis_max;
		dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		while ( dist0_1 <= min_dist_anthills) {
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		}
		std::cout << "There are 2 Anthills at:" << std::endl;
		std::cout << anthill_x_pos[0] << ", " << anthill_y_pos[0] << std::endl;
		std::cout << anthill_x_pos[1] << ", " << anthill_y_pos[1] << std::endl;
	}
	else if (numAnthill == 3) {
		// 3 Anthills
		anthill_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		anthill_y_pos[0] = rand() % y_axis_max;
		anthill_x_pos[1] = rand() % x_axis_max;
		anthill_y_pos[1] = rand() % y_axis_max;
		anthill_x_pos[2] = rand() % x_axis_max;
		anthill_y_pos[2] = rand() % y_axis_max;
		dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		while (dist0_1 <= min_dist_anthills) {
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		}
		dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
		dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));
		while (dist0_2 <= min_dist_anthills || dist1_2 <= min_dist_anthills) {
			anthill_x_pos[2] = rand() % x_axis_max;
			anthill_y_pos[2] = rand() % y_axis_max;
			dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
			dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));
		}
		std::cout << "There are 3 Anthills at:" << std::endl;
		std::cout << anthill_x_pos[0] << ", " << anthill_y_pos[0] << std::endl;
		std::cout << anthill_x_pos[1] << ", " << anthill_y_pos[1] << std::endl;
		std::cout << anthill_x_pos[2] << ", " << anthill_y_pos[2] << std::endl;
	}
	else if (numAnthill == 4) {
		// 4 Anthills
		anthill_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		anthill_y_pos[0] = rand() % y_axis_max;
		anthill_x_pos[1] = rand() % x_axis_max;
		anthill_y_pos[1] = rand() % y_axis_max;
		anthill_x_pos[2] = rand() % x_axis_max;
		anthill_y_pos[2] = rand() % y_axis_max;
		anthill_x_pos[3] = rand() % x_axis_max;
		anthill_y_pos[3] = rand() % y_axis_max;
		// make sure first two points are far enough away
		dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		while (dist0_1 <= min_dist_anthills) {
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		}
		// make sure 3rd point is far enough away
		dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
		dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));
		while (dist0_2 <= min_dist_anthills || dist1_2 <= min_dist_anthills) {
			anthill_x_pos[2] = rand() % x_axis_max;
			anthill_y_pos[2] = rand() % y_axis_max;
			dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
			dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));
		}
		// make sure 4th point is far enough away
		dist0_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[0], 2));
		dist1_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[1], 2));
		dist2_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[2], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[2], 2));
		while (dist0_3 <= min_dist_anthills || dist1_3 <= min_dist_anthills || dist2_3 <= min_dist_anthills) {
			anthill_x_pos[3] = rand() % x_axis_max;
			anthill_y_pos[3] = rand() % y_axis_max;
			dist0_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[0], 2));
			dist1_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[1], 2));
			dist2_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[2], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[2], 2));
		}
		std::cout << "There are 4 Anthills at:" << std::endl;
		std::cout << anthill_x_pos[0] << ", " << anthill_y_pos[0] << std::endl;
		std::cout << anthill_x_pos[1] << ", " << anthill_y_pos[1] << std::endl;
		std::cout << anthill_x_pos[2] << ", " << anthill_y_pos[2] << std::endl;
		std::cout << anthill_x_pos[3] << ", " << anthill_y_pos[3] << std::endl;
	}
	else {
		// ERROR. ASSUME 2 Anthills
		anthill_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		anthill_y_pos[0] = rand() % y_axis_max;
		anthill_x_pos[1] = rand() % x_axis_max;
		anthill_y_pos[1] = rand() % y_axis_max;
		dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		while (dist0_1 <= min_dist_anthills) {
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		}
		std::cout << "ERROR CASE HIT IN ANTHILL SELECTOR" << std::endl;
		std::cout << "There are 2 Anthills at:" << std::endl;
		std::cout << anthill_x_pos[0] << ", " << anthill_y_pos[0] << std::endl;
		std::cout << anthill_x_pos[1] << ", " << anthill_y_pos[1] << std::endl;
	}
	
	// Randomly pick Crumbs
	if (numCrumb == 1) {
		// 1 Crumb
		crumb_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		crumb_y_pos[0] = rand() % y_axis_max;
		while (dist0_1 <= min_dist_crumbs) {
			crumb_x_pos[0] = rand() % x_axis_max;
			crumb_y_pos[0] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		}
		std::cout << "There is 1 Crumb at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
	}
	else if (numAnthill == 2) {
		// 2 Crumb
		
		std::cout << "There are 2 Crumbs at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
		std::cout << crumb_x_pos[1] << ", " << crumb_y_pos[1] << std::endl;
	}
	else if (numAnthill == 3) {
		// 3 Anthills
		
		std::cout << "There are 3 Crumbs at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
		std::cout << crumb_x_pos[1] << ", " << crumb_y_pos[1] << std::endl;
		std::cout << crumb_x_pos[2] << ", " << crumb_y_pos[2] << std::endl;
	}
	else if (numAnthill == 4) {
		// 4 Anthills
		
		
		std::cout << "There are 4 Crumbs at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
		std::cout << crumb_x_pos[1] << ", " << crumb_y_pos[1] << std::endl;
		std::cout << crumb_x_pos[2] << ", " << crumb_y_pos[2] << std::endl;
		std::cout << crumb_x_pos[3] << ", " << crumb_y_pos[3] << std::endl;
	}
	else {
		// ERROR. ASSUME 2 Anthills
		
		std::cout << "ERROR CASE HIT IN CRUMB SELECTOR" << std::endl;
		std::cout << "There is 1 Crumb at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
	}

	Visual v = Visual();

	while (/*runSim && timeTick < 10 && */ runSim && !glfwWindowShouldClose(v.getWindow())) {

		// exit with ESC
		if (glfwGetKey(v.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(v.getWindow(), GL_TRUE);
			runSim = false;
			break;
		}

		// time ticks at ms/tick
		// This while loop is where the simulation should happen
		std::cout << "Entered Main While loop" << std::endl;
		// If crumbs are empty and if Anthills are all searching
		// end while loop
		//runSim = false; // this needs to be in the check
		timeTick += 1;

		// OpenGL visualization
		float* anthills = new float[numAnthill * 3];
		for (int i = 0; i < numAnthill; i++) {
			anthills[3 * i] = anthill_x_pos[i] / 1000.0f - 1.0f;
			anthills[3 * i + 1] = anthill_y_pos[i] / 1000.0f - 1.0f;
			anthills[3 * i + 2] = 0.5f;
		}
		float* crumbs = new float[numCrumb * 3];
		for (int i = 0; i < numCrumb; i++) {
			crumbs[3 * i] = crumb_x_pos[i] / 1000.0f - 1.0f;
			crumbs[3 * i + 1] = crumb_y_pos[i] / 1000.0f - 1.0f;
			crumbs[3 * i + 2] = 0.5f;
		}
		float circles[] = {0.0f, 0.0f, 0.0f, 0.0f};
		v.displayGraphicsInnerLoop(numAnthill, anthills, numCrumb, crumbs, circles); //num_anthills, anthills, num_breadcrumbs, breadcrumbs, circles);
	}
	//std::cin >> cont;

	v.teardown();

	return 0;

}
