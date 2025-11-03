/*
* Author: Shawn Douglas
* Assignment Title: Group Subway Surfers Project
* Assignment Description: A subway surfers classic inspired
                        project.
* Due Date: 12/09/2025
* Date Created: 10/09/2025
* Date Last Modified: 10/19/2025
*/

#include "functions.h"

int main()
{
    
    // Data Abstraction:
    const int WIDTH = 1000;
    const int HEIGHT = 1000;
    const int SPEED = 5;
    const int PLAYER_SIZE = 5;
    const Coord ORIGIN = {WIDTH / 2, HEIGHT / 2};
    const color COIN_COLOR;
    
    color playerColor;
    Uint32 RGB;
    int userScore = 0;
    Circle player;
    
    int px = ORIGIN.x;
    int py = ORIGIN.y;
    
    int dx = 0;
    int dy = 0;
    
    
    // Input:
    
    // Process:
    SDL_Plotter g(WIDTH, HEIGHT);
    
    while (!g.getQuit()) {
        g.clear();
        
        // Input:
        if (g.kbhit()) {
            switch(g.getKey()) {
                case UP_ARROW:
                    dy = -SPEED;
                    dx = 0;
                    break;
                case DOWN_ARROW:
                    dy = SPEED;
                    dx = 0;
                    break;
                case LEFT_ARROW:
                    dx = -SPEED;
                    dy = 0;
                    break;
                case RIGHT_ARROW:
                    dx = SPEED;
                    dy = 0;
                    break;
            }
        }
        
        px += dx;
        py += dy;
        
        
        CreatePlayer({px, py}, PLAYER_SIZE, playerColor, g);
        
        g.update();
        g.Sleep(10);
    }
    
    // Output:
    
    // Assumptions:
    
    return 0;
}
