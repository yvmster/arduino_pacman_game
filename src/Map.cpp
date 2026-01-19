#include "Map.h"
#include <avr/pgmspace.h>
#include <string.h>

// Классический лабиринт Pac-Man 28x31 (PROGMEM)
// 0 = пустое место, 1 = стена, 2 = точка, 3 = power pellet
const uint8_t MAZE_DATA[MAP_HEIGHT][MAP_WIDTH] PROGMEM = {
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
    initDotState();
    DEBUG_PRINTLN(FLASH_STR("[MAP] Map initialized"));
    DEBUG_PRINT(FLASH_STR("[MAP] Total dots: "));
    DEBUG_PRINTLN(dotsCount);
}

void Map::reset() {
    initDotState();
    DEBUG_PRINTLN(FLASH_STR("[MAP] Map reset to initial state"));
}

void Map::initDotState() {
    memset(dotState, 0, sizeof(dotState));
    dotsCount = 0;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            uint8_t tile = getBaseTile(x, y);
            uint16_t index = y * MAP_WIDTH + x;

            if (tile == TILE_DOT) {
                setDotState(index, 1);
                dotsCount++;
            } else if (tile == TILE_POWER) {
                setDotState(index, 2);
                dotsCount++;
            }
        }
    }
}

uint8_t Map::getBaseTile(int x, int y) const {
    return pgm_read_byte(&MAZE_DATA[y][x]);
}

uint8_t Map::getDotState(uint16_t index) const {
    uint16_t bitIndex = index * 2;
    uint16_t byteIndex = bitIndex / 8;
    uint8_t shift = bitIndex % 8;
    uint8_t value = (dotState[byteIndex] >> shift) & 0x03;

    if (shift > 6) {
        uint8_t nextBits = dotState[byteIndex + 1] & 0x01;
        value |= (nextBits << 1);
    }

    return value;
}

void Map::setDotState(uint16_t index, uint8_t value) {
    uint16_t bitIndex = index * 2;
    uint16_t byteIndex = bitIndex / 8;
    uint8_t shift = bitIndex % 8;

    dotState[byteIndex] &= ~(0x03 << shift);
    dotState[byteIndex] |= ((value & 0x03) << shift);

    if (shift > 6) {
        dotState[byteIndex + 1] &= ~0x01;
        dotState[byteIndex + 1] |= ((value >> 1) & 0x01);
    }
}

bool Map::isValidPos(int x, int y) const {
    return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
}

bool Map::isWall(int x, int y) const {
    if (!isValidPos(x, y)) {
        return true;
    }
    return getBaseTile(x, y) == TILE_WALL;
}

bool Map::hasDot(int x, int y) const {
    if (!isValidPos(x, y)) {
        return false;
    }
    uint16_t index = y * MAP_WIDTH + x;
    return getDotState(index) == 1;
}

bool Map::hasPower(int x, int y) const {
    if (!isValidPos(x, y)) {
        return false;
    }
    uint16_t index = y * MAP_WIDTH + x;
    return getDotState(index) == 2;
}

int Map::eatDot(int x, int y) {
    if (!isValidPos(x, y)) {
        return 0;
    }

    uint16_t index = y * MAP_WIDTH + x;
    uint8_t state = getDotState(index);
    int points = 0;

    if (state == 1) {
        points = POINTS_DOT;
        setDotState(index, 0);
        dotsCount--;
        DEBUG_PRINT(FLASH_STR("[MAP] Dot eaten at ("));
        DEBUG_PRINT(x);
        DEBUG_PRINT(FLASH_STR(", "));
        DEBUG_PRINT(y);
        DEBUG_PRINT(FLASH_STR("), +"));
        DEBUG_PRINT(points);
        DEBUG_PRINTLN(FLASH_STR(" points"));
    } else if (state == 2) {
        points = POINTS_POWER;
        setDotState(index, 0);
        dotsCount--;
        DEBUG_PRINT(FLASH_STR("[MAP] Power pellet eaten at ("));
        DEBUG_PRINT(x);
        DEBUG_PRINT(FLASH_STR(", "));
        DEBUG_PRINT(y);
        DEBUG_PRINT(FLASH_STR("), +"));
        DEBUG_PRINT(points);
        DEBUG_PRINTLN(FLASH_STR(" points"));
    }

    return points;
}

uint8_t Map::getTile(int x, int y) const {
    if (!isValidPos(x, y)) {
        return TILE_WALL;
    }

    uint8_t baseTile = getBaseTile(x, y);
    if (baseTile == TILE_DOT || baseTile == TILE_POWER) {
        uint16_t index = y * MAP_WIDTH + x;
        uint8_t state = getDotState(index);
        if (state == 1) {
            return TILE_DOT;
        }
        if (state == 2) {
            return TILE_POWER;
        }
        return TILE_EMPTY;
    }

    return baseTile;
}

void Map::setTile(int x, int y, uint8_t tile) {
    if (!isValidPos(x, y)) {
        return;
    }

    uint16_t index = y * MAP_WIDTH + x;
    if (tile == TILE_DOT) {
        setDotState(index, 1);
    } else if (tile == TILE_POWER) {
        setDotState(index, 2);
    } else {
        setDotState(index, 0);
    }
}

uint16_t Map::getDotsRemaining() const {
    return dotsCount;
}

bool Map::isLevelComplete() const {
    return dotsCount == 0;
}
