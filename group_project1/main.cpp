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
#include "classes.h"

int main()
{
    
    // Data Abstraction:
    const int WIDTH = 900;
    const int HEIGHT = 600;
    const int PLAYER_SPEED = 40;
    const int PLAYER_SIZE = 20;
    const int CHASER_SIZE = 25;
    const int COIN_SIZE = 10;
    const int CHASER_SPEED = 25;
    const int POWER_UP_SIZE = 15;
    const int ROAD_MARK_GAP = 150;
    const color POWER_UP_COLOR(0, 255, 0);
    const point PLAYER_ORIGIN(WIDTH / 2, HEIGHT - 200);
    const point CHASER_ORIGIN(WIDTH / 2, HEIGHT - 100);
    const color COIN_COLOR(255, 215, 0);
    const color CHASER_COLOR(255, 0, 0);
    const color LANE_BORDER_COLOR(0, 0, 0);
    const color BACKGROUND_COLOR(100, 100, 100);
    
    point playerPos;
    point chaserPos;
    point powerUpPos;
    point backgroundOrigin(0, 0);
    
    Rectangle background;
    
    vector<point> coins;
    vector<point> train;
    vector<Rectangle> trainCars;
    
    color playerColor;
    color trainColor(50, 50, 50);
    double playerPoints = 0;
    double playerScore = 0;
    
    int dx = 0, dxC = 0;
    int laneNum = 2;
    int laneWidth = WIDTH / 3;
    int leftEdge, rightEdge;
    char key;
    
    int coinSpawnChance = 10;
    int powerUpSpawnChance = 1000;
    int trainSpawnChance = 500;
    
    int objectSpeed = 10;
    int trainSpeed = objectSpeed - 2;
    
    int line1X = laneWidth;
    int line2X = 2 * laneWidth;
    
    bool active = true;
    
    SDL_Plotter g(HEIGHT, WIDTH);
    
    
    // Input:
    
    // Process:
    srand(time(NULL));

    background.setWidth(WIDTH);
    background.setHeight(HEIGHT);
    background.setColor(BACKGROUND_COLOR);
    
    playerPos.x = PLAYER_ORIGIN.x;
    playerPos.y = PLAYER_ORIGIN.y;
    chaserPos.x = CHASER_ORIGIN.x;
    chaserPos.y = CHASER_ORIGIN.y;
    leftEdge = 0;
    rightEdge = WIDTH - PLAYER_SIZE;

    
    
    while (!g.getQuit()) {
        g.clear();
        
        background.drawRectangle(backgroundOrigin, g);
        
        // Input:
        if (g.kbhit()) {
            key = g.getKey();
            if ((key == LEFT_ARROW || key == 'a') && laneNum > 1) {
                laneNum--;
                dx = -PLAYER_SPEED;
                dxC = -CHASER_SPEED;
            }
            else if ((key == RIGHT_ARROW || key == 'd') && laneNum < 3) {
                laneNum++;
                dx = PLAYER_SPEED;
                dxC = CHASER_SPEED;
            }
        }
        
        // Process:
        
        if (coins.empty() || coins.back().y > 150) {
            placeCoinRow(coins, WIDTH, coinSpawnChance);
        }
        
        updateCoins(coins, objectSpeed, HEIGHT);
        drawCoins(coins, COIN_SIZE, COIN_COLOR, g);
        
        if (train.empty()) {
            placeTrain(train, trainCars, WIDTH, trainSpawnChance);
        }
        
        updateTrain(train, HEIGHT, trainSpeed, trainSpawnChance, trainColor);
        drawTrain(train, trainCars, g, trainColor);
        
        laneSwitch(playerPos, WIDTH, PLAYER_SPEED, laneNum, dx);
        laneSwitch(chaserPos, WIDTH, CHASER_SPEED, laneNum, dxC);
        createModel(playerPos, PLAYER_SIZE, playerColor, g);
        
        createModel(chaserPos, CHASER_SIZE, CHASER_COLOR, g);
        updatePoints(playerPos, coins, playerPoints, PLAYER_SIZE, COIN_SIZE);
        
        createModel(powerUpPos, POWER_UP_SIZE, POWER_UP_COLOR, g);
        updatePowerUp(powerUpPos, WIDTH, HEIGHT, objectSpeed, active, powerUpSpawnChance);
        
        
        
        // collision handling
        if (detectCollision(playerPos, powerUpPos, PLAYER_SIZE, POWER_UP_SIZE)) {
            powerUpPos.y += 1000; // remove from screen
            objectSpeed += 5;
            trainSpeed += 5;
        }
        
        
        
        setBorders(playerPos, leftEdge, rightEdge);
        
        drawVerticalLine(g, line1X, HEIGHT, 0, LANE_BORDER_COLOR);
        drawVerticalLine(g, line2X, HEIGHT, 0, LANE_BORDER_COLOR);
        
        g.update();
        g.Sleep(10);
    }
    
    // Output:
    
    
    // Assumptions:
    
    return 0;
}
