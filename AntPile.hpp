//  AntPile.hpp
//  4122_final_project


#ifndef AntPile_hpp
#define AntPile_hpp

#include <stdio.h>
#include <string>
#include "Bread.hpp"

using namespace std;

class AntPile {
    
    public:
    
        // Initializer (user specifies type, population and pile location)
        AntPile(int type, int pop, double xcoord, double ycoord);
    
        // Setters (there's only one data member that will be changed)
        void setRadius(double radius);

        // Getters (all of these will be accessed for math calculations / radius updates
        string getSpecies();
        double getXcoord();
        double getYcoord();
        double getSpeed();
        bool getEating();
        double getRadius();
        double getFoodRadius();
        double getCarryCap();
        int getOutRate();
        Bread getBreadcrumb();
        void radiusRun();
    
        // Misc. Functions
         void printInfo(); // use for debugging and object creation
    
    
    private:
    
        string species; // will be set to "Black" "Red" "Fire" or "Bullet" etc on initialization
        double x, y; // x,y coordinates
        double speed; // in m/s, varies by ant type
        double searchRadius; // radius of current search circle
        double foodRadius;
        double carryCap; // carrying capacity of ant
        bool eating;
        Bread breadcrumb;
        int outRate;
        int currentOut;

};

#endif /* AntPile_hpp */
