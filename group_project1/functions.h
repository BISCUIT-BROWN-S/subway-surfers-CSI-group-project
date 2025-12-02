#include "SDL_Plotter.h"
#include "classes.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

/*
 description: check if the last key pressed is valid
 return: void
 precondition: none
 postcondition: generates player model (circle)
*/

void createModel(point, int, color, SDL_Plotter&);

void setBorders(point&, int, int);

int getLaneCenter(int, const int);

void shuffleLanes(vector<int>&);

void laneSwitch(point&, const int, const int, int, int&);

void placeCoinRow(vector<point>&, const int, int);

void updateCoins(vector<point>&, const int, const int);

void drawCoins(vector<point>&, const int, const color, SDL_Plotter&);

void updatePoints(point&, vector<point>&, double&, int, const int);

void drawVerticalLine(SDL_Plotter&, int, int, int, color);

void drawHorizontalLine(SDL_Plotter&, int, int, int, color);

void updatePowerUp(point&, const int, const int, int, bool&, int);

bool detectCollision(point&, point&, int, int);

void placeTrain(vector<point>&, vector<Rectangle>&, const int, int);

void updateTrain(vector<point>&, const int, int, int, color);

void drawTrain(vector<point>&, vector<Rectangle>&, SDL_Plotter&, color);

bool trainHitStatus(vector<point>&, vector<Rectangle>&);



#endif
