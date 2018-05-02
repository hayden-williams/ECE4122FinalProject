//  AntPile.cpp
//  4122_final_project


#include <string>
#include <iostream>
#include <cmath>
#include "AntPile.hpp"
using namespace std;

/*AntPile::AntPile() {
    x = 0; // give ant pile randomly generated x coord from main
    y = 0; // give ant pile randomly generated y coord from main
    searchRadius = 0.0; // initializes to zero?

    switch (0) {

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
}*/

AntPile::AntPile(int type, double xcoord, double ycoord) {
    
    x = xcoord; // give ant pile randomly generated x coord from main
    y = ycoord; // give ant pile randomly generated y coord from main
    searchRadius = 0.0; // initializes to zero?
    length = 0.0;
    foodRadius = 0.0;
    eating = false;
    currentOut = 0;
    
    switch (type) {
            
        case 0: // black ant
            species = "Black Ant";
            speed = 0.45; // in mm/ms
            carryCap = 13; // in mg
            outRate = 2;
            break;
        case 1: // red ant
            species = "Red Ant";
            speed = 0.50; // in mm/ms
            carryCap = 15; // in mg
            outRate = 3;
            break;
        case 2: // fire ant
            species = "Fire Ant";
            speed = 0.55; // in mm/ms
            carryCap = 17; // in mg
            outRate = 4;
            break;
        case 3: // bullet ant
            species = "Bullet Ant";
            speed = 0.60; // in mm/ms
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

double AntPile::getLength() {
    return length;
};


Bread AntPile::getBreadcrumb() {
    return breadcrumb;
};

double AntPile::getFoodRadius() {
    return foodRadius;
};

int AntPile::getOutRate() {
    return outRate;
};

void AntPile::radiusRun(Bread **crumbs, int numCrumb) {
    searchRadius = searchRadius + speed;
    for (int i = 0; i < numCrumb; i++) {
        Bread* c = crumbs[i];
        if((c->getXcoord() > 0 || c->getYcoord() > 0) && (c->getMass() != 0)) {
            double pythag = sqrt(pow(x - c->getXcoord(), 2) + pow(y - c->getYcoord(), 2));
            std::cout<<pythag<<endl;
            std::cout << searchRadius<< endl;
            if (pythag <= searchRadius) {
                std::cout << "in if" << endl;
                eating = true;
                breadcrumb = *c;
                foodRadius = searchRadius;
            }
        }
    }
};

void AntPile::eat(Bread breadcrumb) {
    if(searchRadius > 0) {
        searchRadius = searchRadius - speed;
    } else {
        if (length < foodRadius) {
            length = length + speed;
        } else {
            if(breadcrumb.getMass() > 0) {
                std::cout<<breadcrumb.getMass()<<endl;
                std::cout<<""<<endl;
                if(currentOut == outRate) {
                    std::cout<< "in if"<<endl;
                    std::cout<<breadcrumb.getMass() - carryCap<<endl;
                    double newMass = breadcrumb.getMass() - carryCap;
                    breadcrumb.setMass(newMass);
                    currentOut = 0;
                } else {
                    currentOut++;
                }
            } else {
                if(length * 2 > 0) {
                    length = length - speed;
                } else {
                    searchRadius = 0;
                    foodRadius = 0;
                    length = 0;
                    eating = false;
                }
            }
        }

    }
};


void AntPile::printInfo() {
    cout << "Pile Location: (" << x << "," << y << ")" << endl;
    cout << "Species: " << species << endl;
    //cout << "Population: " << population << endl;
    cout << "Ant Speed: " << speed << endl;
    cout << "Carrying Capacity: " << carryCap << endl;
    cout << "Current Search Radius: " << searchRadius << endl;
    cout << endl << endl;
};










