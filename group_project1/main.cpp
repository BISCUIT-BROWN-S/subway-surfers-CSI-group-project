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
#include "structs.h"

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
    const int SPEED_BOOST_SIZE = 15;
    const int IMMUNITY_SIZE = 20;
    const color SPEED_BOOST_COLOR(0, 255, 0);
    const color IMMUNITY_COLOR(0, 0, 255);
    const point PLAYER_ORIGIN(WIDTH / 2, HEIGHT - 200);
    const point CHASER_ORIGIN(WIDTH / 2, HEIGHT - 100);
    const color COIN_COLOR(255, 215, 0);
    const color LANE_BORDER_COLOR(0, 0, 0);
    const color BACKGROUND_COLOR(150, 150, 150);
    
    // sound variables
    Mix_Chunk* coinEffect;
    Mix_Chunk* speedBoostEffect;
    Mix_Chunk* immunityEffect;
    Mix_Chunk* impactEffect;
    Mix_Chunk* moveEffect;
    
    Uint32 startTime;
    Uint32 currentTime;
    Uint32 timeCollect = 0.0;
    float timeSinceCollect = 0.0;
    float timeElapsed;
    
    point playerPos(PLAYER_ORIGIN.x, PLAYER_ORIGIN.y);
    point chaserPos(CHASER_ORIGIN.x, CHASER_ORIGIN.y);
    point speedBoostPos;
    point immunityPos;
    point backgroundOrigin(0, 0);
    
    Rectangle background;
    
    vector<point> coins;
    vector<point> train;
    vector<Rectangle> trainCars;
    
    color playerColor(0, 0, 0);
    color chaserColor(255, 0, 0);
    color trainColor(50, 50, 50);
    double playerPoints = 0;
    double playerScore = 0;
    
    int dxP = 0, dxC = 0;
    int laneNum = 2;
    int laneWidth = WIDTH / 3;
    int leftEdge, rightEdge;
    char key;
    
    // game phases/states
    bool StartMenu;
    bool Game;
    bool Death;
    
    int coinSpawnChance = 10;
    int speedBoostSpawnChance = 1000;
    int immunitySpawnChance = 500;
    int trainSpawnChance = 500;
    
    int objectSpeed = 10;
    int trainSpeed = objectSpeed - 2;
    
    int line1X = laneWidth;
    int line2X = 2 * laneWidth;
    
    bool active = true;
    bool immunityActive = false;
    
    SDL_Plotter g(HEIGHT, WIDTH);
    
    
    // Input:
    
    // Process:
    srand(time(NULL));
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    coinEffect = Mix_LoadWAV("Sounds/impactGlass_heavy_000.wav");
    immunityEffect = Mix_LoadWAV("Sounds/impactBell_heavy_000.wav");
    impactEffect = Mix_LoadWAV("Sounds/impactPlate_light_004.wav");
    moveEffect = Mix_LoadWAV("Sounds/phaserDown2.wav");

    background.width = WIDTH;
    background.height = HEIGHT;
    background.c = BACKGROUND_COLOR;
    
    leftEdge = 0;
    rightEdge = WIDTH - PLAYER_SIZE;
    
    startTime = SDL_GetTicks();
    
    while (!g.getQuit()) {
        g.clear();
        
        background.drawRectangle(backgroundOrigin, g);
        
        currentTime = SDL_GetTicks();
        timeElapsed = (currentTime - startTime) / 1000.0;
        
        // Input:
        if (g.kbhit()) {
            key = g.getKey();
            Mix_PlayChannel(-1, moveEffect, 0);
            if (!moveEffect) {
                printf("Failed to load moveEffect: %s\n", Mix_GetError());
            }
            if ((key == LEFT_ARROW || key == 'a') && laneNum > 1) {
                laneNum--;
                dxP = -PLAYER_SPEED;
                dxC = -CHASER_SPEED;
            }
            else if ((key == RIGHT_ARROW || key == 'd') && laneNum < 3) {
                laneNum++;
                dxP = PLAYER_SPEED;
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
        
        laneSwitch(playerPos, WIDTH, PLAYER_SPEED, laneNum, dxP);
        laneSwitch(chaserPos, WIDTH, CHASER_SPEED, laneNum, dxC);
        createPlayerModel(playerPos, PLAYER_SIZE, playerColor, g);
        
        createPlayerModel(chaserPos, CHASER_SIZE, chaserColor, g);
        updatePoints(playerPos, coins, playerPoints, PLAYER_SIZE, COIN_SIZE, coinEffect);
        
        createModel(speedBoostPos, SPEED_BOOST_SIZE, SPEED_BOOST_COLOR, g);
        updatePowerUp(speedBoostPos, WIDTH, HEIGHT, objectSpeed, active,
                      speedBoostSpawnChance);
        
        createModel(immunityPos, IMMUNITY_SIZE, IMMUNITY_COLOR, g);
        updatePowerUp(immunityPos, WIDTH, HEIGHT, objectSpeed, active,
                      immunitySpawnChance);
        
        
        // timing handling
        /* FIX ME!!!
        if (timeElapsed > 10) {
            updateChaserPos(chaserPos, HEIGHT, CHASER_SIZE, -objectSpeed);
        }
        */
        
        // collision handling
        if (detectCollision(playerPos, speedBoostPos, PLAYER_SIZE, SPEED_BOOST_SIZE)) {
            speedBoostPos.y += 1000; // remove from screen
            objectSpeed += 5;
            trainSpeed += 5;
            Mix_PlayChannel(-1, speedBoostEffect, 0);
        }
        
        if (detectCollision(playerPos, immunityPos, PLAYER_SIZE, IMMUNITY_SIZE)) {
            immunityPos.y += 1000; // remove from screen
            timeCollect = SDL_GetTicks();
            immunityActive = true;
            Mix_PlayChannel(-1, immunityEffect, 0);
        }
        
        if (immunityActive) {
            timeSinceCollect = (currentTime - timeCollect) / 1000.0;
            objectSpeed = 40;
            trainSpeed = 35;
            if (timeSinceCollect >= 20.0) {
                immunityActive = false;
                objectSpeed = 10;
                trainSpeed = objectSpeed - 2;
            }
        }

        
        if (!immunityActive) {
            if (detectTrainCollision(playerPos, train, trainCars, PLAYER_SIZE)) {
                objectSpeed = 0;
                trainSpeed = 0;
                Mix_PlayChannel(-1, impactEffect, 0);
            }
        }
        
        setBorders(playerPos, leftEdge, rightEdge);
        
        drawVerticalLine(g, line1X, HEIGHT, 0, LANE_BORDER_COLOR);
        drawVerticalLine(g, line2X, HEIGHT, 0, LANE_BORDER_COLOR);
        
        g.update();
        g.Sleep(10);
    }
    
    Mix_CloseAudio();
    
    // Output:
    
    
    // Assumptions:
    
    return 0;
}
