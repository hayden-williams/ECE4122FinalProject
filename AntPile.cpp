//
//  AntPile.cpp
//  4122_final_project
//
//  Created by Javi Rodriguez on 4/22/18.
//  Copyright © 2018 Georgia Tech. All rights reserved.
//

#include "AntPile.hpp"
#include <string>
#include <iostream>
using namespace std;

AntPile::AntPile(int type, int pop, double xcoord, double ycoord) {
    
    x = xcoord; // give ant pile randomly generated x coord from main
    y = ycoord; // give ant pile randomly generated y coord from main
    population = pop; // give ant pile randomly generated population from main
    searchRadius = 0.0; // initializes to zero?
    
    switch (type) {
            
        case 0: // black ant
            species = "Black Ant";
            speed = 0.045; // in m/s
            carryCap = 13; // in mg
            break;
        case 1: // red ant
            species = "Red Ant";
            speed = 0.050; // in m/s
            carryCap = 15; // in mg
            break;
        case 2: // fire ant
            species = "Fire Ant";
            speed = 0.055; // in m/s
            carryCap = 17; // in mg
            break;
        case 3: // bullet ant
            species = "Bullet Ant";
            speed = 0.060; // in m/s
            carryCap = 19; // in mg
            break;
            
    }
    
};

void AntPile::setRadius(double radius) {
    searchRadius = radius;
};

string AntPile::getSpecies() {
    return species;
};

double AntPile::getXcoord() {
    return x;
};

double AntPile::getYcoord() {
    return y;
};

double AntPile::getSpeed() {
    return speed;
};

int AntPile::getPopulation() {
    return population;
};

double AntPile::getRadius() {
    return searchRadius;
};

double AntPile::getCarryCap() {
    return carryCap;
};

void AntPile::printInfo() {
    cout << "Pile Location: (" << x << "," << y << ")" << endl;
    cout << "Species: " << species << endl;
    cout << "Population: " << population << endl;
    cout << "Ant Speed: " << speed << endl;
    cout << "Carrying Capacity: " << carryCap << endl;
    cout << "Current Search Radius: " << searchRadius << endl;
    cout << endl << endl;
};










