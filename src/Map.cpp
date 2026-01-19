#include "Map.h"

// Классический лабиринт Pac-Man 28x31
// 0 = пустое место, 1 = стена, 2 = точка, 3 = power pellet
const uint8_t MAZE_DATA[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,3,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,3,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
    {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,4,4,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,4,4,4,4,4,4,1,0,1,1,2,1,1,1,1,1,1},
    {0,0,0,0,0,0,2,0,0,0,1,4,4,4,4,4,4,1,0,0,0,2,0,0,0,0,0,0},
    {1,1,1,1,1,1,2,1,1,0,1,4,4,4,4,4,4,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
    {1,3,2,2,1,1,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,1,1,2,2,3,1},
    {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
    {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
    {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Map::Map() : dotsCount(0) {
}

void Map::init() {
    loadMapData();
    countDots();
    DEBUG_PRINTLN("[MAP] Map initialized");
    DEBUG_PRINT("[MAP] Total dots: ");
    DEBUG_PRINTLN(dotsCount);
}

void Map::reset() {
    loadMapData();
    countDots();
    DEBUG_PRINTLN("[MAP] Map reset to initial state");
}

void Map::loadMapData() {
    // Копируем данные карты из PROGMEM в RAM
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            tiles[y][x] = MAZE_DATA[y][x];
        }
    }
}

void Map::countDots() {
    dotsCount = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (tiles[y][x] == TILE_DOT || tiles[y][x] == TILE_POWER) {
                dotsCount++;
            }
        }
    }
}

bool Map::isValidPos(int x, int y) const {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

bool Map::isWall(int x, int y) const {
    if (!isValidPos(x, y)) {
        return true;  // За пределами карты считаем стеной
    }
    return tiles[y][x] == TILE_WALL;
}

bool Map::hasDot(int x, int y) const {
    if (!isValidPos(x, y)) {
        return false;
    }
    return tiles[y][x] == TILE_DOT;
}

bool Map::hasPower(int x, int y) const {
    if (!isValidPos(x, y)) {
        return false;
    }
    return tiles[y][x] == TILE_POWER;
}

int Map::eatDot(int x, int y) {
    if (!isValidPos(x, y)) {
        return 0;
    }

    int points = 0;
    
    if (tiles[y][x] == TILE_DOT) {
        points = POINTS_DOT;
        tiles[y][x] = TILE_EMPTY;
        dotsCount--;
        DEBUG_PRINT("[MAP] Dot eaten at (");
        DEBUG_PRINT(x);
        DEBUG_PRINT(", ");
        DEBUG_PRINT(y);
        DEBUG_PRINT("), +");
        DEBUG_PRINT(points);
        DEBUG_PRINTLN(" points");
    } 
    else if (tiles[y][x] == TILE_POWER) {
        points = POINTS_POWER;
        tiles[y][x] = TILE_EMPTY;
        dotsCount--;
        DEBUG_PRINT("[MAP] Power pellet eaten at (");
        DEBUG_PRINT(x);
        DEBUG_PRINT(", ");
        DEBUG_PRINT(y);
        DEBUG_PRINT("), +");
        DEBUG_PRINT(points);
        DEBUG_PRINTLN(" points");
    }

    return points;
}

uint8_t Map::getTile(int x, int y) const {
    if (!isValidPos(x, y)) {
        return TILE_WALL;  // За пределами = стена
    }
    return tiles[y][x];
}

void Map::setTile(int x, int y, uint8_t tile) {
    if (isValidPos(x, y)) {
        tiles[y][x] = tile;
    }
}

int Map::getDotsRemaining() const {
    return dotsCount;
}

bool Map::isLevelComplete() const {
    return dotsCount == 0;
}
