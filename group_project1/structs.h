#ifndef STRUCTS_H
#define STRUCTS_H
#include "SDL_Plotter.h"

struct Rectangle {
    int width = 100;
    int height = 200;
    color c;
    
    /*
     description: draws a rectangle with the dimensions of a Rectangle object
     return: void
     precondition: plotPixel() must exist
     postcondition: none
    */
    void drawRectangle(point&, SDL_Plotter&);
    
};

#endif
