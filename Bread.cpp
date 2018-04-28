//  Bread.cpp
//  4122_final_project


#include <iostream>
#include "Bread.hpp"
using namespace std;

Bread::Bread(double size, double xcoord, double ycoord) {
    
    mass = size; // initialize to randomly generated size size
    x = xcoord; // initialize to randomly generated coordinate
    y = ycoord;
    
}


void Bread::setMass(double size) {
    mass = size;
}

double Bread::getMass() {
    return mass;
}

double Bread::getXcoord() {
    return x;
}

double Bread::getYcoord() {
    return y;
}

void Bread::printInfo() {
    cout << "Bread Location: (" << x << "," << y << ")" << endl;
    cout << "Mass remaning: " << mass << "mg" << endl;
    cout << endl << endl;
};
