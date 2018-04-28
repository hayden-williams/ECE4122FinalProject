//  AntPile.h
//  4122_final_project


#ifndef AntPile_hpp
#define AntPile_hpp

#include <stdio.h>
#include <string>

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
        int getPopulation();
        double getRadius();
        double getCarryCap();
    
        // Misc. Functions
         void printInfo(); // use for debugging and object creation
    
    
    private:
    
        string species; // will be set to "Black" "Red" "Fire" or "Bullet" etc on initialization
        double x, y; // x,y coordinates
        double speed; // in m/s, varies by ant type
        int population; //
        double searchRadius; // radius of current search circle
        double carryCap; // carring capacity of ant
    
    
};

#endif /* AntPile_hpp */
