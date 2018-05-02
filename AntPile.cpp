//  AntPile.cpp
//  4122_final_project


#include <string>
#include <iostream>
#include <cmath>
#include "AntPile.hpp"
using namespace std;

AntPile::AntPile(int type, int pop, double xcoord, double ycoord) {
    
    x = xcoord; // give ant pile randomly generated x coord from main
    y = ycoord; // give ant pile randomly generated y coord from main
    searchRadius = 0.0; // initializes to zero?
    
    switch (type) {
            
        case 0: // black ant
            species = "Black Ant";
            speed = 0.045; // in mm/ms
            carryCap = 13; // in mg
            outRate = 2;
            break;
        case 1: // red ant
            species = "Red Ant";
            speed = 0.050; // in mm/ms
            carryCap = 15; // in mg
            outRate = 3;
            break;
        case 2: // fire ant
            species = "Fire Ant";
            speed = 0.055; // in mm/ms
            carryCap = 17; // in mg
            outRate = 4;
            break;
        case 3: // bullet ant
            species = "Bullet Ant";
            speed = 0.060; // in mm/ms
            carryCap = 19; // in mg
            outRate = 5;
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

bool AntPile::getEating() {
    return eating;
};

double AntPile::getRadius() {
    return searchRadius;
};

double AntPile::getCarryCap() {
    return carryCap;
};

Bread AntPile::getBreadcrumb() {
    return breadcrumb;
};

Bread AntPile::getFoodRadius() {
    return foodRadius;
};

int AntPile::getOutRate() {
    return outRate;
};

void AntPile::radiusRun(Bread *crumbs) {
    searchRadius = searchRadius + speed;
    for(c: crumbs) {
        pythag = pow(abs(x - c.getXcoord), 2) + pow(abs(y- c.getYcoord), 2);
        if(pythag <= searchRadius) {
            eating = true;
            breadcrumb = x;
            foodRadius = searchRadius;
        }
    }
};

void AntPile::eat(Bread breadcrumb) {
    if(searchRadius > 0) {
        searchRadius = searchRadius - speed;
    } else {
        if (searchRadius < foodRadius) {
            searchRadius = searchRadius + speed;
        } else {
            if(breadcrumb.getMass > 0) {
                if(currentOut == outRate) {
                    breadcrumb.setMass(breadcrumb.getMass - carryCap);
                    currentOut = 0;
                } else {
                    currentOut++;
                }
            } else {
                if(foodRadius * 2 > 0) {
                    foodRadius = foodRadius - speed;
                } else {
                    searchRadius = 0;
                    foodRadius = 0;
                    eating = false;
                }
            }
        }

    }
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










