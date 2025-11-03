#include "functions.h"

void CreatePlayer(Coord loc, int size, color c, SDL_Plotter& g) {
    for(double i = -size; i <= size;i += 0.1){
        for(double j = -size; j <= size; j += 0.1){
            if(i * i + j * j <= size * size){
                g.plotPixel(round(loc.x + i), round(loc.y + j), c);
            }
        }
    }
}
