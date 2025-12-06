#include "structs.h"
#include "functions.h"

void Rectangle::drawRectangle(point& loc, SDL_Plotter& s) {
    
    for (int y = loc.y; y < (loc.y + height); ++y) {
        for (int x = loc.x; x < (loc.x + width); ++x) {
            s.plotPixel(x, y, c);
        }
    }
}
