#include "SDL_Plotter.h"
#include "structs.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

/*
 description: creates a circular model
 return: void
 precondition: plotPixel() must exist
 postcondition: generates player model (circle)
*/
void createModel(point&, int, color, SDL_Plotter&);

/*
 description: creates the player models
 return: void
 precondition: createModel() and drawRect() must exist
 postcondition: none
*/
void createPlayerModel(point&, int, color, SDL_Plotter&);

/*
 description: creates the model for the immunithy orb
 return: void
 precondition: createModel() must exist
 postcondition: none
*/
void createImmunityModel(point&, int, color, SDL_Plotter&);

/*
 description: sets the borders for the map
 return: void
 precondition: none
 postcondition: none
*/
void setBorders(point&, int, int);

/*
 description: returns the lane center of each lane
 return: void
 precondition: lane number must be between 1 and 3
 postcondition: none
*/
int getLaneCenter(int, const int);

/*
 description: shuffles the lane order
 return: void
 precondition: none
 postcondition: none
*/
void shuffleLanes(vector<int>&);

/*
 description: allows the player model to switch lanes
 return: void
 precondition: none
 postcondition: none
*/
void laneSwitch(point&, const int, int, int, int&);

/*
 description: initializes a vector with coins
 return: void
 precondition: none
 postcondition: none
*/
void placeCoinRow(vector<point>&, const int, int);

/*
 description: sets the borders for the map
 return: void
 precondition: none
 postcondition: none
*/
void updateCoins(vector<point>&, const int, const int);

/*
 description: draws the coin models at the top of the map
 return: void
 precondition: none
 postcondition: none
*/
void drawCoins(vector<point>&, const int, const color, SDL_Plotter&);

/*
 description: updates the players points upon colliding with a coin
 return: void
 precondition: none
 postcondition: none
*/
void updatePoints(point&, vector<point>&, int&, int, const int, Mix_Chunk*);

/*
 description: draws a vertical line down the map (for lane seperators)
 return: void
 precondition: plotPixel() must exist
 postcondition: none
*/
void drawVerticalLine(SDL_Plotter&, int, int, int, color);

/*
 description: updates the position of any singular power up
 return: void
 precondition: none
 postcondition: none
*/
void updatePowerUp(point&, const int, const int, int, bool&, int);

/*
 description: detects a collision between two points
 return: bool
 precondition: none
 postcondition: none
*/
bool detectCollision(point&, point&, int, int);

/*
 description: fills the train position and rectangle vector with points and cars respectively
              and only allows for trains to take up at most two lanes at once
 return: void
 precondition: shuffleLanes() must exist
 postcondition: none
*/
void placeTrain(vector<point>&, vector<Rectangle>&, const int, int);

/*
 description: updates the trains position
 return: void
 precondition: none
 postcondition: none
*/
void updateTrain(vector<point>&, const int, int, int, color);

/*
 description: updates the players points upon colliding with a coin
 return: void
 precondition: drawRect() must exist
 postcondition: none
*/
void drawTrain(vector<point>&, vector<Rectangle>&, SDL_Plotter&, color);

/*
 description: detects a collision between the player model and a rectangle object
 return: bool
 precondition: none
 postcondition: none
*/
bool detectRectCollision(point&, point&, int, Rectangle);

/*
 description: detects a collision between the player and any of the train cars
              in a given train
 return: bool
 precondition: detectRectCollision() must exist
 postcondition: none
*/
bool detectTrainCollision(point&, vector<point>&, vector<Rectangle>&, int);

/*
 description: erases any elements that spawn in vectors (i.e. trains and coins)
 return: void
 precondition: none
 postcondition: none
*/
void eraseRow(vector<point>&);

#endif
