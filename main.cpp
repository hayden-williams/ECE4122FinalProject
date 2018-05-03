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
#include "AntPile.hpp"
#include "Bread.hpp"

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
double dist0c_1a = 0;
double dist0c_2a = 0;
double dist0c_3a = 0;
double dist0c_1c = 0;
double dist0c_2c = 0;
double dist0c_3c = 0;
double dist1c_0a = 0;
double dist1c_1a = 0;
double dist1c_2a = 0;
double dist1c_3a = 0;
double dist1c_2c = 0;
double dist1c_3c = 0;
double dist2c_0a = 0;
double dist2c_1a = 0;
double dist2c_2a = 0;
double dist2c_3a = 0;
double dist2c_3c = 0;
double dist3c_0a = 0;
double dist3c_1a = 0;
double dist3c_2a = 0;
double dist3c_3a = 0;

int cont; //used input to pause cmd line output
std::string userInput;
int count = 0;

uint32_t decrimentCounter = 1; // counter for while loops, start at 1!
uint32_t max_num_loops_initiation = 30; //max num of while loops before reducing max_dist


AntPile* antObj0 = nullptr;
AntPile* antObj1 = nullptr;
AntPile* antObj2 = nullptr;
AntPile* antObj3 = nullptr;
Bread* crumbObj0 = nullptr;
Bread* crumbObj1 = nullptr;
Bread* crumbObj2 = nullptr;
Bread* crumbObj3 = nullptr;


int main() {
    srand(time(NULL));
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
		decrimentCounter = 1;
		while ( dist0_1 <= min_dist_anthills) {
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));

			// safety if while loop runs too long
			if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_anthills -= 1; }
			decrimentCounter += 1;
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
		decrimentCounter = 1;
		while (dist0_1 <= min_dist_anthills) {
            std::cout<<"Died after this 1 \n"<<endl;
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));

			// safety if while loop runs too long
			if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_anthills -= 1; }
			decrimentCounter += 1;
		}
        std::cout<<"Died after this 2 \n"<<endl;
		dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
		dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));
		decrimentCounter = 1;
		while (dist0_2 <= min_dist_anthills || dist1_2 <= min_dist_anthills) {
            std::cout<<"Died after this 3 \n"<<endl;
			anthill_x_pos[2] = rand() % x_axis_max;
			anthill_y_pos[2] = rand() % y_axis_max;
			dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
			dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));

			// safety if while loop runs too long
			if (decrimentCounter % max_num_loops_initiation == 0) {min_dist_anthills -= 1; }
			decrimentCounter += 1;
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
		decrimentCounter = 1;
		while (dist0_1 <= min_dist_anthills) {
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));

			// safety if while loop runs too long
			if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_anthills -= 1; }
			decrimentCounter += 1;
		}
		// make sure 3rd point is far enough away
		dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
		dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));
		decrimentCounter = 1;
		while (dist0_2 <= min_dist_anthills || dist1_2 <= min_dist_anthills) {
            std::cout<<"Died after this 4 \n"<<endl;
			anthill_x_pos[2] = rand() % x_axis_max;
			anthill_y_pos[2] = rand() % y_axis_max;
			dist0_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[0], 2));
			dist1_2 = std::sqrt(std::pow(anthill_x_pos[2] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[2] - anthill_y_pos[1], 2));

			// safety if while loop runs too long
			if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_anthills -= 1; }
			decrimentCounter += 1;
		}
		// make sure 4th point is far enough away
		dist0_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[0], 2));
		dist1_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[1], 2));
		dist2_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[2], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[2], 2));
		decrimentCounter = 1;
		while (dist0_3 <= min_dist_anthills || dist1_3 <= min_dist_anthills || dist2_3 <= min_dist_anthills) {
			anthill_x_pos[3] = rand() % x_axis_max;
			anthill_y_pos[3] = rand() % y_axis_max;
			dist0_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[0], 2));
			dist1_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[1], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[1], 2));
			dist2_3 = std::sqrt(std::pow(anthill_x_pos[3] - anthill_x_pos[2], 2) + std::pow(anthill_y_pos[3] - anthill_y_pos[2], 2));

			// safety if while loop runs too long
			if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_anthills -= 1; }
			decrimentCounter += 1;
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
		numAnthill = 2;
		dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));
		decrimentCounter = 1;
		while (dist0_1 <= min_dist_anthills) {
			anthill_x_pos[1] = rand() % x_axis_max;
			anthill_y_pos[1] = rand() % y_axis_max;
			dist0_1 = std::sqrt(std::pow(anthill_x_pos[1] - anthill_x_pos[0], 2) + std::pow(anthill_y_pos[1] - anthill_y_pos[0], 2));

			// safety if while loop runs too long
			if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_anthills -= 1; }
			decrimentCounter += 1;
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
		if (numAnthill == 2) {
			// only compare to the 2 anthills
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 3) {
			// 3 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 4) {
			// 4 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else {
			// Default: Assume 4 anthills (since the extras will just be at 0,0)
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}

		std::cout << "There is 1 Crumb at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
	}
	else if (numCrumb == 2) {
		// 2 Crumbs
		crumb_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		crumb_y_pos[0] = rand() % y_axis_max;
		crumb_x_pos[1] = rand() % x_axis_max;
		crumb_y_pos[1] = rand() % y_axis_max;

		if (numAnthill == 2) {
			// only compare to the 2 anthills
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs || dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 3) {
			// 3 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs ||
				   dist0c_2a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs || dist1c_2a <= min_dist_crumbs || dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 4) {
			// 4 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs ||
				   dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs ||
				   dist1c_2a <= min_dist_crumbs || dist1c_3a <= min_dist_crumbs ||
				   dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else {
			// Default: Assume 4 anthills (since the extras will just be at 0,0)
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs ||
				   dist1c_2a <= min_dist_crumbs || dist1c_3a <= min_dist_crumbs ||
				   dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		std::cout << "There are 2 Crumbs at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
		std::cout << crumb_x_pos[1] << ", " << crumb_y_pos[1] << std::endl;
	}
	else if (numCrumb == 3) {
		// 3 Crumbs
		crumb_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		crumb_y_pos[0] = rand() % y_axis_max;
		crumb_x_pos[1] = rand() % x_axis_max;
		crumb_y_pos[1] = rand() % y_axis_max;
		crumb_x_pos[2] = rand() % x_axis_max;
		crumb_y_pos[2] = rand() % y_axis_max;

		if (numAnthill == 2) {
			// only compare to the 2 anthills
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs || dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist0c_2c <= min_dist_crumbs || dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 3) {
			// 3 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs ||
				   dist0c_2a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs || dist1c_2a <= min_dist_crumbs || dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist2c_2a <= min_dist_crumbs || dist0c_2c <= min_dist_crumbs ||
				   dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 4) {
			// 4 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs ||
				   dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs ||
				   dist1c_2a <= min_dist_crumbs || dist1c_3a <= min_dist_crumbs ||
				   dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
			dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist2c_2a <= min_dist_crumbs || dist2c_3a <= min_dist_crumbs ||
				   dist0c_2c <= min_dist_crumbs || dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
				dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else {
            std::cout<<"Dieddddd \n"<<endl;
			// Default: Assume 4 anthills (since the extras will just be at 0,0)
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs ||
				   dist1c_2a <= min_dist_crumbs || dist1c_3a <= min_dist_crumbs ||
				   dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
			dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist2c_2a <= min_dist_crumbs || dist2c_3a <= min_dist_crumbs ||
				   dist0c_2c <= min_dist_crumbs || dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
				dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		std::cout << "There are 3 Crumbs at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
		std::cout << crumb_x_pos[1] << ", " << crumb_y_pos[1] << std::endl;
		std::cout << crumb_x_pos[2] << ", " << crumb_y_pos[2] << std::endl;
	}
	else if (numCrumb == 4) {
		// 4 Crumbs
		crumb_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		crumb_y_pos[0] = rand() % y_axis_max;
		crumb_x_pos[1] = rand() % x_axis_max;
		crumb_y_pos[1] = rand() % y_axis_max;
		crumb_x_pos[2] = rand() % x_axis_max;
		crumb_y_pos[2] = rand() % y_axis_max;
		crumb_x_pos[3] = rand() % x_axis_max;
		crumb_y_pos[3] = rand() % y_axis_max;

		if (numAnthill == 2) {
			// only compare to the 2 anthills
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs || dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist0c_2c <= min_dist_crumbs || dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
			dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
			dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
			dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
			dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist3c_0a <= min_dist_crumbs || dist3c_1a <= min_dist_crumbs ||
				   dist0c_3c <= min_dist_crumbs || dist1c_3c <= min_dist_crumbs ||
				   dist2c_3c <= min_dist_crumbs ) {
				crumb_x_pos[3] = rand() % x_axis_max;
				crumb_y_pos[3] = rand() % y_axis_max;
				dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
				dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
				dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
				dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
				dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 3) {
			// 3 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs ||
				   dist0c_2a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs || dist1c_2a <= min_dist_crumbs || dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist2c_2a <= min_dist_crumbs || dist0c_2c <= min_dist_crumbs ||
				   dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
			dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
			dist3c_2a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[2], 2));
			dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
			dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
			dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist3c_0a <= min_dist_crumbs || dist3c_1a <= min_dist_crumbs ||
				   dist3c_2a <= min_dist_crumbs || dist0c_3c <= min_dist_crumbs ||
				   dist1c_3c <= min_dist_crumbs || dist2c_3c <= min_dist_crumbs) {
				crumb_x_pos[3] = rand() % x_axis_max;
				crumb_y_pos[3] = rand() % y_axis_max;
				dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
				dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
				dist3c_2a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[2], 2));
				dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
				dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
				dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 4) {
			// 4 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs ||
				   dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs ||
				   dist1c_2a <= min_dist_crumbs || dist1c_3a <= min_dist_crumbs ||
				   dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
			dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist2c_2a <= min_dist_crumbs || dist2c_3a <= min_dist_crumbs ||
				   dist0c_2c <= min_dist_crumbs || dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
				dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
			dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
			dist3c_2a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[2], 2));
			dist3c_3a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[3], 2));
			dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
			dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
			dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist3c_0a <= min_dist_crumbs || dist3c_1a <= min_dist_crumbs ||
				   dist3c_2a <= min_dist_crumbs || dist3c_3a <= min_dist_crumbs ||
				   dist0c_3c <= min_dist_crumbs || dist1c_3c <= min_dist_crumbs ||
				   dist2c_3c <= min_dist_crumbs) {
				crumb_x_pos[3] = rand() % x_axis_max;
				crumb_y_pos[3] = rand() % y_axis_max;
				dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
				dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
				dist3c_2a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[2], 2));
				dist3c_3a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[3], 2));
				dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
				dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
				dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else {
			// Default: Assume 4 anthills (since the extras will just be at 0,0)
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
			dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
			dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
			dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
			dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist1c_0a <= min_dist_crumbs || dist1c_1a <= min_dist_crumbs ||
				   dist1c_2a <= min_dist_crumbs || dist1c_3a <= min_dist_crumbs ||
				   dist0c_1c <= min_dist_crumbs) {
				crumb_x_pos[1] = rand() % x_axis_max;
				crumb_y_pos[1] = rand() % y_axis_max;
				dist1c_0a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[0], 2));
				dist1c_1a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[1], 2));
				dist1c_2a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[2], 2));
				dist1c_3a = std::sqrt(std::pow(crumb_x_pos[1] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[1] - anthill_y_pos[3], 2));
				dist0c_1c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[1], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
			dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
			dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
			dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
			dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
			dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist2c_0a <= min_dist_crumbs || dist2c_1a <= min_dist_crumbs ||
				   dist2c_2a <= min_dist_crumbs || dist2c_3a <= min_dist_crumbs ||
				   dist0c_2c <= min_dist_crumbs || dist1c_2c <= min_dist_crumbs) {
				crumb_x_pos[2] = rand() % x_axis_max;
				crumb_y_pos[2] = rand() % y_axis_max;
				dist2c_0a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[0], 2));
				dist2c_1a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[1], 2));
				dist2c_2a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[2], 2));
				dist2c_3a = std::sqrt(std::pow(crumb_x_pos[2] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[2] - anthill_y_pos[3], 2));
				dist0c_2c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[2], 2));
				dist1c_2c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[2], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
			dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
			dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
			dist3c_2a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[2], 2));
			dist3c_3a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[3], 2));
			dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
			dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
			dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist3c_0a <= min_dist_crumbs || dist3c_1a <= min_dist_crumbs ||
				   dist3c_2a <= min_dist_crumbs || dist3c_3a <= min_dist_crumbs ||
				   dist0c_3c <= min_dist_crumbs || dist1c_3c <= min_dist_crumbs ||
				   dist2c_3c <= min_dist_crumbs) {
				crumb_x_pos[3] = rand() % x_axis_max;
				crumb_y_pos[3] = rand() % y_axis_max;
				dist3c_0a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[0], 2));
				dist3c_1a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[1], 2));
				dist3c_2a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[2], 2));
				dist3c_3a = std::sqrt(std::pow(crumb_x_pos[3] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[3] - anthill_y_pos[3], 2));
				dist0c_3c = std::sqrt(std::pow(crumb_x_pos[0] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[0] - crumb_y_pos[3], 2));
				dist1c_3c = std::sqrt(std::pow(crumb_x_pos[1] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[1] - crumb_y_pos[3], 2));
				dist2c_3c = std::sqrt(std::pow(crumb_x_pos[2] - crumb_x_pos[3], 2) + std::pow(crumb_y_pos[2] - crumb_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		std::cout << "There are 4 Crumbs at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
		std::cout << crumb_x_pos[1] << ", " << crumb_y_pos[1] << std::endl;
		std::cout << crumb_x_pos[2] << ", " << crumb_y_pos[2] << std::endl;
		std::cout << crumb_x_pos[3] << ", " << crumb_y_pos[3] << std::endl;
	}
	else {
        std::cout<<"Deadddd \n"<<endl;
		// ERROR. ASSUME 1 Crumb

		crumb_x_pos[0] = rand() % x_axis_max; // may what to add to it if too close to border
		crumb_y_pos[0] = rand() % y_axis_max;
		numCrumb = 1;
		if (numAnthill == 2) {
			// only compare to the 2 anthills
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 3) {
			// 3 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else if (numAnthill == 4) {
			// 4 anthills to compare to
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}
		else {
			// Default: Assume 4 anthills (since the extras will just be at 0,0)
			dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
			dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
			dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
			dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));
			decrimentCounter = 1;
			while (dist0c_0a <= min_dist_crumbs || dist0c_1a <= min_dist_crumbs || dist0c_2a <= min_dist_crumbs || dist0c_3a <= min_dist_crumbs) {
				crumb_x_pos[0] = rand() % x_axis_max;
				crumb_y_pos[0] = rand() % y_axis_max;
				dist0c_0a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[0], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[0], 2));
				dist0c_1a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[1], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[1], 2));
				dist0c_2a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[2], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[2], 2));
				dist0c_3a = std::sqrt(std::pow(crumb_x_pos[0] - anthill_x_pos[3], 2) + std::pow(crumb_y_pos[0] - anthill_y_pos[3], 2));

				// safety if while loop runs too long
				if (decrimentCounter % max_num_loops_initiation == 0) { min_dist_crumbs -= 1; }
				decrimentCounter += 1;
			}
		}

		std::cout << "ERROR CASE HIT IN CRUMB SELECTOR" << std::endl;
		std::cout << "There is 1 Crumb at:" << std::endl;
		std::cout << crumb_x_pos[0] << ", " << crumb_y_pos[0] << std::endl;
	}

	// create anthill and crumb objects
	if (numAnthill == 2) {
		// Create object here
		// AntPile(int type, double xcoord, double ycoord)
		//AntPile antObj0(2,anthill_x_pos[0],anthill_y_pos[0]);
		//AntPile antObj1(0,anthill_x_pos[1],anthill_y_pos[1]);
		antObj0 = new AntPile(2,anthill_x_pos[0],anthill_y_pos[0]);
		antObj1 = new AntPile(0,anthill_x_pos[1],anthill_y_pos[1]);
	}
	else if (numAnthill == 3) {
		// Create object here
		//AntPile antObj0(2,anthill_x_pos[0],anthill_y_pos[0]);
		//AntPile antObj1(0,anthill_x_pos[1],anthill_y_pos[1]);
		//AntPile antObj2(1,anthill_x_pos[2],anthill_y_pos[2]);
		antObj0 = new AntPile(2,anthill_x_pos[0],anthill_y_pos[0]);
		antObj1 = new AntPile(0,anthill_x_pos[1],anthill_y_pos[1]);
		antObj2 = new AntPile(1,anthill_x_pos[2],anthill_y_pos[2]);
	}
	else {
		// Create object here
		//AntPile antObj0(2,anthill_x_pos[0],anthill_y_pos[0]);
		//AntPile antObj1(0,anthill_x_pos[1],anthill_y_pos[1]);
		//AntPile antObj2(1,anthill_x_pos[2],anthill_y_pos[2]);
		//AntPile antObj3(3,anthill_x_pos[3],anthill_y_pos[3]);
		antObj0 = new AntPile(2,anthill_x_pos[0],anthill_y_pos[0]);
		antObj1 = new AntPile(0,anthill_x_pos[1],anthill_y_pos[1]);
		antObj2 = new AntPile(1,anthill_x_pos[2],anthill_y_pos[2]);
		antObj3 = new AntPile(3,anthill_x_pos[3],anthill_y_pos[3]);
	}

	if (numCrumb == 1) {
		// Create object here
		//Bread crumbObj0(42,crumb_x_pos[0],crumb_y_pos[0],0);
		crumbObj0 = new Bread(42,crumb_x_pos[0],crumb_y_pos[0],0);
	}
	else if (numCrumb == 2) {
		// Create object here
		//Bread crumbObj0(42,crumb_x_pos[0],crumb_y_pos[0],0);
		//Bread crumbObj1(6,crumb_x_pos[1],crumb_y_pos[1],1);
		crumbObj0 = new Bread(42,crumb_x_pos[0],crumb_y_pos[0],0);
		crumbObj1 = new Bread(222,crumb_x_pos[1],crumb_y_pos[1],1);
	}
	else if (numCrumb == 3) {
		// Create object here
		//Bread crumbObj0(42,crumb_x_pos[0],crumb_y_pos[0],0);
		//Bread crumbObj1(6,crumb_x_pos[1],crumb_y_pos[1],1);
		//Bread crumbObj2(68,crumb_x_pos[2],crumb_y_pos[2],2);
		crumbObj0 = new Bread(42,crumb_x_pos[0],crumb_y_pos[0],0);
		crumbObj1 = new Bread(6,crumb_x_pos[1],crumb_y_pos[1],1);
		crumbObj2 = new Bread(68,crumb_x_pos[2],crumb_y_pos[2],2);
	}
	else {
		// Create object here
		//Bread crumbObj0(42,crumb_x_pos[0],crumb_y_pos[0],0);
		//Bread crumbObj1(6,crumb_x_pos[1],crumb_y_pos[1],1);
		//Bread crumbObj2(68,crumb_x_pos[2],crumb_y_pos[2],2);
		//Bread crumbObj3(55,crumb_x_pos[3],crumb_y_pos[3],3);
		crumbObj0 = new Bread(42,crumb_x_pos[0],crumb_y_pos[0],0);
		crumbObj1 = new Bread(6,crumb_x_pos[1],crumb_y_pos[1],1);
		crumbObj2 = new Bread(68,crumb_x_pos[2],crumb_y_pos[2],2);
		crumbObj3 = new Bread(35,crumb_x_pos[3],crumb_y_pos[3],3);
	}



	// create array of objects for anthills and crumbs
	Bread *crumbs[4];
	crumbs[0] = crumbObj0;
	crumbs[1] = crumbObj1;
	crumbs[2] = crumbObj2;
	crumbs[3] = crumbObj3;

	Visual v = Visual();


	while (runSim && !glfwWindowShouldClose(v.getWindow())) {
		// exit with ESC
		if (glfwGetKey(v.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(v.getWindow(), GL_TRUE);
			runSim = false;
			break;
		}

		// time ticks at ms/tick
		// This while loop is where the simulation should happen
		//std::cout << "Entered Main While loop" << std::endl;
		// If crumbs are empty and if Anthills are all searching
		// end while loop
		timeTick += 1;
        if(numAnthill == 4) {
            if (antObj0->getDone() && antObj1->getDone() && antObj2->getDone() && antObj3->getDone()){
                std::cout<<"Amounts collected:"<<endl;
                std::cout<< antObj0->getSpecies() + "; " + std::to_string(antObj0->getCollected()) <<endl;
                std::cout<< antObj1->getSpecies() + "; " + std::to_string(antObj1->getCollected()) <<endl;
                std::cout<< antObj2->getSpecies() + "; " + std::to_string(antObj2->getCollected()) <<endl;
                std::cout<< antObj3->getSpecies() + "; " + std::to_string(antObj3->getCollected()) <<endl;
                break;
            }
        }

        if(numAnthill == 3) {
            if (antObj0->getDone() && antObj1->getDone() && antObj2->getDone()){
                std::cout<<"Amounts collected:"<<endl;
                std::cout<< antObj0->getSpecies() + "; " + std::to_string(antObj0->getCollected()) <<endl;
                std::cout<< antObj1->getSpecies() + "; " + std::to_string(antObj1->getCollected()) <<endl;
                std::cout<< antObj2->getSpecies() + "; " + std::to_string(antObj2->getCollected()) <<endl;
                break;
            }
        }

        if(numAnthill == 2) {
            if (antObj0->getDone() && antObj1->getDone()){
                std::cout<<"Amounts collected:"<<endl;
                std::cout<< antObj0->getSpecies() + "; " + std::to_string(antObj0->getCollected()) <<endl;
                std::cout<< antObj1->getSpecies() + "; " + std::to_string(antObj1->getCollected()) <<endl;
                break;
            }
        }


        double sradius0 = antObj0->getRadius();
		double pathToFood0 = antObj0->getLength();
		double sradius1 = antObj1->getRadius();
		double pathToFood1 = antObj1->getLength();

		double sradius2 = 0;
		double sradius3 = 0;
		double pathToFood2 = 0;
		double pathToFood3 = 0;

		if(numAnthill > 2) {
			sradius2 = antObj2->getRadius();
			pathToFood2 = antObj2->getLength();
		}
		if(numAnthill > 3) {
			sradius3 = antObj3->getRadius();
			pathToFood3 = antObj3->getLength();
		}


		if(!antObj0->getEating()) {
            antObj0->radiusRun(crumbs, numCrumb);
		}
        if(!antObj1->getEating()) {
            antObj1->radiusRun(crumbs, numCrumb);
        }
        if(numAnthill > 2) {
            if (!antObj2->getEating() && numAnthill > 2) {
                antObj2->radiusRun(crumbs, numCrumb);
            }
        }
        if(numAnthill > 3) {
            if (!antObj3->getEating() && numAnthill > 3) {
                antObj3->radiusRun(crumbs, numCrumb);
            }
        }


        Bread* eatingCrumb2;
        Bread* eatingCrumb3;

        Bread* eatingCrumb0 = antObj0->getBreadcrumb();
		Bread* eatingCrumb1 = antObj1->getBreadcrumb();
        if(numAnthill > 2) eatingCrumb2 = antObj2->getBreadcrumb();
        if(numAnthill > 3) eatingCrumb3 = antObj3->getBreadcrumb();

		int crumb0 = 0;
		int crumb1 = 0;
		int crumb2 = 0;
		int crumb3 = 0;

        if(antObj0->getEating()) {
        	crumb0 = eatingCrumb0->getNumbread();;
            antObj0->eat(eatingCrumb0);
        }
        if(antObj1->getEating()) {
        	crumb1 = eatingCrumb1->getNumbread();
            antObj1->eat(eatingCrumb1);
        }
        if(numAnthill > 2) {
            if(antObj2->getEating() && numAnthill > 2) {
                crumb2 = eatingCrumb2->getNumbread();
                antObj2->eat(eatingCrumb2);
            }
        }
        if(numAnthill > 3) {
            if (antObj3->getEating() && numAnthill > 3) {
                crumb3 = eatingCrumb3->getNumbread();
                antObj3->eat(eatingCrumb3);
            }
        }


		// OpenGL visualization
		// array of anthills: x pos, y pos, size
		float* anthills = new float[numAnthill * 3];
		for (int i = 0; i < numAnthill; i++) {
			anthills[3 * i] = anthill_x_pos[i] / 1000.0f - 1.0f;
			anthills[3 * i + 1] = anthill_y_pos[i] / 1000.0f - 1.0f;
			anthills[3 * i + 2] = 0.25f;
		}
		// array of breadcrumbs: x pos, y pos, size
		float* crumbs = new float[numCrumb * 3];
		for (int i = 0; i < numCrumb; i++) {
			crumbs[3 * i] = crumb_x_pos[i] / 1000.0f - 1.0f;
			crumbs[3 * i + 1] = crumb_y_pos[i] / 1000.0f - 1.0f;
			crumbs[3 * i + 2] = 0.25f;
		}
		// array of radii of "scout ant" circles for each anthill
		float circles[] = { float(sradius0), float(sradius1), float(sradius2), float(sradius3) };
		// array of ant lines for each anthill: target breadcrumb, % of the way there
		float lines[] = { float(crumb0), float(pathToFood0),
						  float(crumb1), float(pathToFood1),
						  float(crumb2), float(pathToFood2),
						  float(crumb3), float(pathToFood3) };
		v.displayGraphicsInnerLoop(numAnthill, anthills, numCrumb, crumbs, circles, lines);

	}

	v.teardown();

	return 0;

}
