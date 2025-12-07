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
    srand(time(NULL));
    
    // Data Abstraction:
    
    // const variables
    const int WIDTH = 900;
    const int HEIGHT = 600;
    const int PLAYER_SPEED = 40;
    const int PLAYER_SIZE = 20;
    const int CHASER_SIZE = 25;
    const int COIN_SIZE = 10;
    const int BOMB_SIZE = 10;
    const int CHASER_SPEED = 25;
    const int SPEED_BOOST_SIZE = 15;
    const int IMMUNITY_SIZE = 20;
    const color SPEED_BOOST_COLOR(0, 255, 0);
    const color IMMUNITY_COLOR(0, 200, 255);
    const point PLAYER_ORIGIN(WIDTH / 2, HEIGHT - 200);
    const point CHASER_ORIGIN(WIDTH / 2, HEIGHT - 100);
    const color COIN_COLOR(255, 215, 0);
    const color LANE_BORDER_COLOR(0, 0, 0);
    const color BOMB_COLOR(255, 0, 0);
    
    // sound variables
    Mix_Chunk* coinEffect;
    Mix_Chunk* speedBoostEffect;
    Mix_Chunk* immunityEffect;
    Mix_Chunk* impactEffect;
    Mix_Chunk* moveEffect;
    Mix_Chunk* clickEffect;
    Mix_Chunk* catchEffect;
    Mix_Chunk* bombEffect;
    
    // text variables
    TTF_Init();
    
    TTF_Font* mainMenuFont = TTF_OpenFont("Fonts/ArcadeClassic.ttf", 50);
    TTF_Font* deathFont = TTF_OpenFont("Fonts/BleedingPixels.ttf", 50);
    
    SDL_Color mainMenuFontColor = {255, 255, 255, 255};
    SDL_Color deathFontColor = {255, 0, 0, 255};
    
    // time variables
    Uint32 startTime;
    Uint32 currentTime;
    Uint32 timeCollect = 0;
    Uint32 now;
    float timeSinceCollect = 0.0;
    float timeElapsed;
    
    // position variables
    point playerPos(PLAYER_ORIGIN.x, PLAYER_ORIGIN.y);
    point chaserPos(CHASER_ORIGIN.x, CHASER_ORIGIN.y);
    point bombPos(-1000, -1000);
    point speedBoostPos(-1000, -1000);
    point immunityPos(-1000, -1000);
    point backgroundOrigin(0, 0);
    
    Rectangle background;
    
    // vector variables
    vector<point> coins;
    vector<point> train;
    vector<Rectangle> trainCars;
    
    // color variables
    color playerColor(0, 0, 0);
    color chaserColor(200, 0, 0);
    color trainColor(50, 50, 50);
    color gameBackgroundColor(150, 150, 150);
    color titleColor(0, 0, 0);
    
    int playerPoints = 0;
    
    int dxP = 0, dxC = 0;
    int laneNum = 2;
    int laneWidth = WIDTH / 3;
    int leftEdge, rightEdge;
    char key;
    
    // game phases/states
    bool menuState = true;
    bool gameState = false;
    bool deathState = false;
    
    // spawn chance variables
    int coinSpawnChance = 10;
    int speedBoostSpawnChance = 1000;
    int immunitySpawnChance = 2000;
    int bombSpawnChance = 300;
    int trainSpawnChance = INT_MAX;
    
    int objectSpeed = 10;
    
    int line1X = laneWidth;
    int line2X = 2 * laneWidth;
    
    bool active = false;
    bool immunityActive = false;
    bool hasHit = false;
    bool secondHit = false;
    bool chaserMovingUp = false;
    
    SDL_Plotter g(HEIGHT, WIDTH);
    
    string deathMessage;
    
    // Process:
    
    // initialize sound
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    coinEffect = Mix_LoadWAV("Sounds/impactGlass_heavy_000.wav");
    immunityEffect = Mix_LoadWAV("Sounds/impactBell_heavy_000.wav");
    speedBoostEffect = Mix_LoadWAV("Sounds/impactBell_heavy_000.wav");
    impactEffect = Mix_LoadWAV("Sounds/impactPlate_light_004.wav");
    moveEffect = Mix_LoadWAV("Sounds/phaserDown2.wav");
    clickEffect = Mix_LoadWAV("Sounds/impactMetal_heavy_002.wav");
    catchEffect = Mix_LoadWAV("Sounds/impactPunch_medium_002.wav");
    bombEffect = Mix_LoadWAV("Sounds/impactWood_medium_001.wav");
    
    
    background.width = WIDTH;
    background.height = HEIGHT;
    
    leftEdge = 0;
    rightEdge = WIDTH - PLAYER_SIZE;
    
    startTime = SDL_GetTicks();
    
    while (!g.getQuit()) {
        g.clear();
        if (menuState) {
            
            // draw text
            g.drawMenu(WIDTH, HEIGHT);
            g.drawText(mainMenuFont, "WELCOME", WIDTH / 2 - 100,
                       200,
                       mainMenuFontColor);
            g.drawText(mainMenuFont, "PRESS  SPACE  TO  PLAY",
                       225, 300, mainMenuFontColor);
            g.present();
            
            if (g.kbhit()) {
                if (g.getKey() == SDLK_SPACE) {
                    Mix_PlayChannel(-1, clickEffect, 0);
                    menuState = false;
                    gameState = true;
                }
            }
        }
        else if (gameState) {
            background.c = gameBackgroundColor;
            background.drawRectangle(backgroundOrigin, g);
            
            currentTime = SDL_GetTicks();
            timeElapsed = (currentTime - startTime) / 1000.0;
            
            // Input:
            if (g.kbhit()) {
                key = g.getKey();
                Mix_PlayChannel(-1, moveEffect, 0);
                
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
            
            laneSwitch(playerPos, WIDTH, PLAYER_SPEED, laneNum, dxP);
            laneSwitch(chaserPos, WIDTH, CHASER_SPEED, laneNum, dxC);
            createPlayerModel(playerPos, PLAYER_SIZE, playerColor, g);
            
            createPlayerModel(chaserPos, CHASER_SIZE, chaserColor, g);
            updatePoints(playerPos, coins, playerPoints, PLAYER_SIZE, COIN_SIZE, coinEffect);
            
            createModel(speedBoostPos, SPEED_BOOST_SIZE, SPEED_BOOST_COLOR, g);
            updatePowerUp(speedBoostPos, WIDTH, HEIGHT, objectSpeed, active,
                          speedBoostSpawnChance);
            
            createImmunityModel(immunityPos, IMMUNITY_SIZE, IMMUNITY_COLOR, g);
            updatePowerUp(immunityPos, WIDTH, HEIGHT, objectSpeed, active,
                          immunitySpawnChance);
            
            createModel(bombPos, BOMB_SIZE, BOMB_COLOR, g);
            updatePowerUp(bombPos, WIDTH, HEIGHT, objectSpeed, active,
                          bombSpawnChance);
            
            if (train.empty()) {
                placeTrain(train, trainCars, WIDTH, trainSpawnChance);
            }
            
            updateTrain(train, HEIGHT, objectSpeed, trainSpawnChance, trainColor);
            drawTrain(train, trainCars, g, trainColor);
            
            // timing handling (progressive difficulty)
            if (timeElapsed > 5 && hasHit == false) {
                trainSpawnChance = 100;
                if (timeElapsed > 20) {
                    trainSpawnChance = 50;
                    bombSpawnChance = 100;
                }
                if (chaserPos.y < HEIGHT + 2 * CHASER_SIZE) {
                    chaserPos.y += objectSpeed;
                }
            }
            
            // collision handling
            if (detectCollision(playerPos, immunityPos, PLAYER_SIZE, IMMUNITY_SIZE)) {
                immunityPos.y += 1000;
                timeCollect = SDL_GetTicks();
                immunityActive = true;
                Mix_PlayChannel(-1, immunityEffect, 0);
            }
            
            if (immunityActive) {
                now = SDL_GetTicks();
                timeSinceCollect = (now - timeCollect) / 1000.0;
                objectSpeed = 40;
                if (timeSinceCollect >= 20.0) {
                    immunityActive = false;
                    objectSpeed = 10;
                }
            }
            
            if (!immunityActive) {
                if (detectCollision(playerPos, bombPos, PLAYER_SIZE, BOMB_SIZE)) {
                    if (hasHit == true) {
                        secondHit = true;
                    }
                    
                    Mix_PlayChannel(-1, bombEffect, 0);
                    bombPos.y += 1000;
                    hasHit = true;
                    chaserMovingUp = true;
                }
            }
            
            if (chaserMovingUp) {
                
                if (secondHit == true) {
                    if (chaserPos.y > playerPos.y) {
                        chaserPos.y -= objectSpeed;
                    }
                    else {
                        chaserMovingUp = false;
                    }
                }
                else {
                    if (chaserPos.y > CHASER_ORIGIN.y) {
                        chaserPos.y -= objectSpeed;
                    }
                    else {
                        chaserMovingUp = false;
                    }
                }
            }
            
            
            
            if (detectCollision(playerPos, chaserPos, PLAYER_SIZE, CHASER_SIZE)) {
                
                Mix_PlayChannel(-1, catchEffect, 0);
                eraseRow(train);
                eraseRow(coins);
                speedBoostPos.y += 1000;
                immunityPos.y += 1000;
                bombPos.y += 1000;
                chaserMovingUp = false;
                secondHit = false;
                
                objectSpeed = 0;
                
                gameState = false;
                deathState = true;
                deathMessage = "you  were  caught";
            }
            
            if (detectCollision(playerPos, speedBoostPos, PLAYER_SIZE, SPEED_BOOST_SIZE)) {
                speedBoostPos.y += 1000;
                objectSpeed += 5;
                Mix_PlayChannel(-1, speedBoostEffect, 0);
            }
            
            if (!immunityActive) {
                if (detectTrainCollision(playerPos, train, trainCars, PLAYER_SIZE)) {
                    Mix_PlayChannel(-1, impactEffect, 0);
                    
                    eraseRow(train);
                    eraseRow(coins);
                    speedBoostPos.y += 1000;
                    immunityPos.y += 1000;
                    
                    objectSpeed = 0;
                    
                    gameState = false;
                    deathState = true;
                    deathMessage = "you  were  hit  by  a  train";
                }
            }
            
            setBorders(playerPos, leftEdge, rightEdge);
            
            drawVerticalLine(g, line1X, HEIGHT, 0, LANE_BORDER_COLOR);
            drawVerticalLine(g, line2X, HEIGHT, 0, LANE_BORDER_COLOR);
            
            g.update();
            g.Sleep(10);
        }
        else if (deathState) {
            g.drawMenu(WIDTH, HEIGHT);
            g.drawText(deathFont, "YOU DIED", 325, 100,
                       deathFontColor);
            g.drawText(deathFont, deathMessage,
                       WIDTH / 2 - (static_cast<int>(deathMessage.length() / 4) * 50) + 20,
                       200, deathFontColor);
            g.drawText(mainMenuFont, "YOUR  SCORE  WAS   "
                       + to_string(playerPoints),
                       250, 300, mainMenuFontColor);
            g.drawText(mainMenuFont, "PRESS  SPACE  TO  RETRY",
                       220, 400, mainMenuFontColor);
            g.present();
            
            if (g.kbhit()) {
                if (g.getKey() == SDLK_SPACE) {
                    Mix_PlayChannel(-1, clickEffect, 0);
                    gameState = true;
                    deathState = false;
                    
                    // reset game
                    startTime = SDL_GetTicks();
                    objectSpeed = 10;
                    playerPoints = 0;
                    playerPos.x = PLAYER_ORIGIN.x;
                    playerPos.y = PLAYER_ORIGIN.y;
                    chaserPos.x = CHASER_ORIGIN.x;
                    chaserPos.y = CHASER_ORIGIN.y;
                    hasHit = false;
                }
            }
        }
    }
    
    Mix_CloseAudio();
    
    TTF_CloseFont(mainMenuFont);
    TTF_CloseFont(deathFont);
    TTF_Quit();
    
    
    // Assumptions:
    
    return 0;
}
