#ifndef STRUCTS_H
#define STRUCTS_H
#include "SDL_Plotter.h"

struct Rectangle {
    int width = 100;
    int height = 200;
    color c;
    
    void drawRectangle(point&, SDL_Plotter&);
    
};

#endif
