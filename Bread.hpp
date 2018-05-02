//  Bread.hpp
//  4122_final_project


#ifndef Bread_hpp
#define Bread_hpp

#include <stdio.h>

class Bread {
    
    public:

        Bread();
        // Initializer (user specifies bread size pile location)
        Bread(double size, double xcoord, double ycoord, int numbread);
    
        // Setters
        void setMass(double size); // mass updated as ants eat
    
        // Getters (will need to be accessed to perform calculations)
        double getMass();
        int getNumbread();
        double getXcoord();
        double getYcoord();
    
        // Misc. Functions
        void printInfo(); // use for debugging and object creation
    
    private:
    
        double mass;
        double x,y;
        int numbread;
    
};

#endif /* Bread_hpp */
