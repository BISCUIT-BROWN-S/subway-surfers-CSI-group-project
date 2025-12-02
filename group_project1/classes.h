#ifndef CLASSES_H
#define CLASSES_H
#include "SDL_Plotter.h"

class Rectangle {
private:
    int width = 100;
    int height = 200;
    color c;
    
public:
    void setHeight(int height) { this->height = height; }
    void setWidth(int width) { this->width = width; }
    void setColor(color c) { this->c = c; }
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    void drawRectangle(point&, SDL_Plotter&);
    
};

#endif
