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

        AntPile();
        // Initializer (user specifies type, population and pile location)
        AntPile(int type, double xcoord, double ycoord);
    
        // Setters (there's only one data member that will be changed)
        void setRadius(double radius);

        // Getters (all of these will be accessed for math calculations / radius updates
        string getSpecies();
        double getXcoord();
        double getYcoord();
        double getSpeed();
        bool getEating();
        bool getDone();
        double getRadius();
        double getFoodRadius();
        double getLength();
        double getCarryCap();
        int getOutRate();
        int getCollected();
        Bread* getBreadcrumb();
        void radiusRun(Bread**, int);
        void eat(Bread*);
    
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
        Bread *breadcrumb;
        int outRate;
        int currentOut;
        double length;
        int collected;
        bool done;

};

#endif /* AntPile_hpp */
