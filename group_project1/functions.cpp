#include "functions.h"
#include<cmath>
#include<vector>

void createModel(point loc, int size, color c, SDL_Plotter& s) {
    for(double i = -size; i <= size;i += 0.1){
        for(double j = -size; j <= size; j += 0.1){
            if(i * i + j * j <= size * size){
                s.plotPixel(round(loc.x + i), round(loc.y + j), c);
            }
        }
    }
}

void createPlayerModel(point loc, int size, color c, SDL_Plotter& s) {
    createModel(loc, size, c, s);
    point headLoc;
    int headSize = size / 2;
    headLoc.x = loc.x;
    headLoc.y = loc.y - (size + 5);
    createModel(headLoc, headSize, c, s);
    
    Rectangle leftLeg;
    point leftLegPos;
    leftLeg.setColor(c);
    leftLeg.setHeight(size);
    leftLeg.setWidth(size / 2);
    leftLegPos.x = loc.x - (size / 2 + leftLeg.getWidth() / 2);;
    leftLegPos.y = loc.y + size / 2;
    leftLeg.drawRectangle(leftLegPos, s);
    
    Rectangle rightLeg;
    point rightLegPos;
    rightLeg.setColor(c);
    rightLeg.setHeight(size);
    rightLeg.setWidth(size / 2);
    rightLegPos.x = loc.x + (size / 2 - rightLeg.getWidth() / 2);
    rightLegPos.y = loc.y + size / 2;
    leftLeg.drawRectangle(rightLegPos, s);
    
    Rectangle leftArm;
    point leftArmPos;
    leftArm.setColor(c);
    leftArm.setHeight(size);
    leftArm.setWidth(size / 2);
    leftArmPos.x = loc.x - (size + leftArm.getWidth() / 2);
    leftArmPos.y = loc.y - size / 2;
    leftArm.drawRectangle(leftArmPos, s);
    
    Rectangle rightArm;
    point rightArmPos;
    rightArm.setColor(c);
    rightArm.setHeight(size);
    rightArm.setWidth(size / 2);
    rightArmPos.x = loc.x + (size - rightArm.getWidth() / 2);
    rightArmPos.y = loc.y - size / 2;
    rightArm.drawRectangle(rightArmPos, s);
}

void setBorders(point& p, int leftLimit, int rightLimit) {
    if (p.x < leftLimit) {
        p.x = leftLimit;
    }
    if (p.x > rightLimit) {
        p.x = rightLimit;
    }
}

int getLaneCenter(int laneNum, const int width) {
    int laneWidth = width / 3;
    return (laneNum - 1) * laneWidth + laneWidth / 2;
}

void shuffleLanes(vector<int>& lanes) {
    for (int i = 0; i < lanes.size(); ++i) {
        int index = rand() % lanes.size();
        swap(lanes[i], lanes[index]);
    }
}

void laneSwitch(point& p, const int width, const int speed, int laneNum, int& dx) {
    int targetX = getLaneCenter(laneNum, width);
    
    if (p.x < targetX) {
        dx = speed;
    }
    else if (p.x > targetX) {
        dx = -speed;
    }
    else {
        dx = 0;
    }
    
    p.x += dx;
    
    if ((dx > 0 && p.x > targetX) || (dx < 0 && p.x < targetX)) {
        p.x = targetX;
        dx = 0;
    }
}

void placeCoinRow(vector<point>& coins, const int width, int spawnChance) {
    if (rand() % spawnChance == 0) {
        int numCoins = rand() % 4 + 1;
        
        for (int i = 0; i < numCoins; ++i) {
            int coinLane = rand() % 3 + 1;
            point coin;
            coin.x = getLaneCenter(coinLane, width);
            coin.y = 0;
            coins.push_back(coin);
        }
    }
}

void updateCoins(vector<point>& coins, int speed, const int map_height) {
    for (unsigned int i = 0; i < coins.size(); ++i) {
        coins[i].y += speed;
        
        if (coins[i].y > map_height) {
            coins.erase(coins.begin() + i);
        }
    }
}

void drawCoins(vector<point>& coins, const int size, color c, SDL_Plotter& s) {
    for (unsigned int i = 0; i < coins.size(); ++i) {
        createModel(coins[i], size, c, s);
    }
}

void updatePoints(point& p, vector<point>& coins, double& points,
                  const int player_size, const int coin_size) {
    for (unsigned int i = 0; i < coins.size(); ++i) {
        if (abs(p.x - coins[i].x) < (player_size + coin_size) &&
            abs(p.y - coins[i].y) < (player_size + coin_size)) {
            
            points++;
            coins.erase(coins.begin() + i);
            i--;
        }
    }
}

void drawVerticalLine(SDL_Plotter& s, int lanePosX, int height, int yInit, color c) {
    for (int y = yInit; y < (yInit + height); ++y) {
        s.plotPixel(lanePosX, y, c);
    }
}

void drawHorizontalLine(SDL_Plotter& s, int lanePosY, int width, int xInit, color c) {
    for (int x = xInit; x < (xInit + width); ++x) {
        s.plotPixel(x, lanePosY, c);
    }
}

void updatePowerUp(point& p, const int map_width, const int map_height, int speed,
                   bool& active, int spawnChance) {
    if (!active) {
        if (rand() % spawnChance == 0) {
            p.x = getLaneCenter(rand() % 3 + 1, map_width);
            p.y = 0;
            active = true;
        }
    }
    
    p.y += speed;
    
    if (p.y > map_height) {
        active = false;
    }
}

bool detectCollision(point& player, point& item, int player_size, int item_size) {
    bool collision = false;
    
    if (abs(player.x - item.x) < (player_size + item_size) &&
        abs(player.y - item.y) < (player_size + item_size)) {
        collision = true;
    }
    
    return collision;
}

void placeTrain(vector<point>& cars, vector<Rectangle>& rects, const int map_width, int spawnChance) {
    vector<int> laneOptions = {1, 2, 3};
    shuffleLanes(laneOptions);
    
    int numTrains = rand() % 2 + 1;
    
    for (int t = 0; t < numTrains; ++t) {
        int laneNum = laneOptions[t];
        
        if (rand() % spawnChance == 0) {
            int numCars = rand() % 3 + 2;
            
            for (int i = 0; i < numCars; ++i) {
                point carPos;
                Rectangle car;
                carPos.x = getLaneCenter(laneNum, map_width) - (car.getWidth() / 2);
                carPos.y = i * -250;
                cars.push_back(carPos);
                rects.push_back(car);
            }
        }
    }
}

void updateTrain(vector<point>& cars, const int map_height, int speed, int spawnChance, color trainColor) {
    for (unsigned int i = 0; i < cars.size(); ++i) {
        cars[i].y += speed;
            
        if (cars.back().y > map_height) {
            cars.erase(cars.begin() + i);
            i--;
        }
    }
}

void drawTrain(vector<point>& cars, vector<Rectangle>& rects, SDL_Plotter& s, color c) {
    for (unsigned int i = 0; i < cars.size(); ++i) {
        rects[i].setColor(c);
        rects[i].drawRectangle(cars[i], s);
        if (i > 0) {
            for (int y = cars[i].y; y < (cars[i].y + 250); ++y) {
                s.plotPixel(cars[i].x + (rects[i].getWidth() / 2), y, c);
            }
        }
    }
}

bool detectRectCollisionX(point& playerPos, point& rectPos, int playerSize, Rectangle r) {
    bool collision = false;
    
    int pLeft = playerPos.x - playerSize / 2;
    int pRight = playerPos.x + playerSize / 2;
    int pTop = playerPos.y - playerSize / 2;
    int pBottom = playerPos.y + playerSize / 2;
    
    
    int rTop = rectPos.y - r.getHeight() / 2;
    int rBottom = rectPos.y + r.getHeight() / 2;
    int rLeft = rectPos.x - r.getWidth() / 2;
    int rRight = rectPos.x + r.getWidth() / 2;
    
    bool verticalOverlap = (pTop < rBottom && pBottom > rTop);

    bool hitLeftSide  = (pRight >= rLeft  && pLeft < rLeft);
    bool hitRightSide = (pLeft <= rRight && pRight > rRight);

    if (verticalOverlap && (hitLeftSide || hitRightSide)) {
        collision = true;
    }
    
    return collision;
}

bool detectRectCollisionY(point& playerPos, point& rectPos, int playerSize, Rectangle r) {
    bool collision = false;
    
    int pLeft = playerPos.x - playerSize / 2;
    int pRight = playerPos.x + playerSize / 2;
    int pTop = playerPos.y - playerSize / 2;
    int pBottom = playerPos.y + playerSize / 2;
    
    int rLeft = rectPos.x - r.getWidth() / 2;
    int rRight = rectPos.x + r.getWidth() / 2;
    int rTop = rectPos.y - r.getHeight() / 2;
    int rBottom = rectPos.y + r.getHeight() / 2;
    
    bool horizontalOverlap = (pLeft < rRight && pRight > rLeft);

    bool hitTop = (pBottom >= rTop && pTop < rTop);
    bool hitBottom = (pTop <= rBottom && pBottom > rBottom);

    if (horizontalOverlap && (hitTop || hitBottom)) {
        collision = true;
    }
        
    return collision;
}


bool detectTrainCollisionY(point& playerPos, vector<point>& train,
                          vector<Rectangle>& trainCars, int player_size) {
    int collision = false;
    for (unsigned int i = 0; i < train.size(); ++i) {
        if (detectRectCollisionY(playerPos, train[i], player_size, trainCars[i])) {
            collision = true;
        }
    }
    
    return collision;
}

bool detectTrainCollisionX(point& playerPos, vector<point>& train,
                          vector<Rectangle>& trainCars, int player_size) {
    int collision = false;
    for (unsigned int i = 0; i < train.size(); ++i) {
        if (detectRectCollisionX(playerPos, train[i], player_size, trainCars[i])) {
            collision = true;
        }
    }
    
    return collision;
}

void updateChaserPos(point& chaserPos, const int map_height, const int chaserSize, int speed) {
    for (int i = chaserPos.y; i < (map_height + chaserSize); ++i) {
        chaserPos.y += speed;
    }
}
