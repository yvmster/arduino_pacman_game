#include "Ghost.h"

Ghost::Ghost() 
    : x(0), y(0), homeX(0), homeY(0), direction(DIR_RIGHT), 
      type(GHOST_BLINKY), moveCounter(0) {
}

void Ghost::init(uint8_t startX, uint8_t startY, GhostType ghostType) {
    x = startX;
    y = startY;
    homeX = startX;
    homeY = startY;
    type = ghostType;
    direction = DIR_RIGHT;
    moveCounter = 0;
    
    DEBUG_PRINT(FLASH_STR("[GHOST] Ghost "));
    DEBUG_PRINT((int)type);
    DEBUG_PRINT(FLASH_STR(" initialized at ("));
    DEBUG_PRINT(x);
    DEBUG_PRINT(FLASH_STR(", "));
    DEBUG_PRINT(y);
    DEBUG_PRINTLN(FLASH_STR(")"));
}

void Ghost::reset() {
    x = homeX;
    y = homeY;
    direction = DIR_RIGHT;
    moveCounter = 0;
}

void Ghost::update(const Player& player, const Map& map) {
    // Управление скоростью движения
    moveCounter++;
    if (moveCounter < GHOST_SPEED) {
        return;
    }
    moveCounter = 0;
    
    // AI: преследование игрока
    chasePlayer(player, map);
}

bool Ghost::collidesWith(uint8_t px, uint8_t py) const {
    return (x == px && y == py);
}

void Ghost::chasePlayer(const Player& player, const Map& map) {
    int8_t px = static_cast<int8_t>(player.getX());
    int8_t py = static_cast<int8_t>(player.getY());
    
    int8_t dx = px - x;
    int8_t dy = py - y;
    
    Direction newDir = direction;
    
    if (abs(dy) > abs(dx)) {
        newDir = (dy > 0) ? DIR_DOWN : DIR_UP;
        if (!canMove(map, newDir)) {
            newDir = (dx > 0) ? DIR_RIGHT : DIR_LEFT;
        }
    } else {
        newDir = (dx > 0) ? DIR_RIGHT : DIR_LEFT;
        if (!canMove(map, newDir)) {
            newDir = (dy > 0) ? DIR_DOWN : DIR_UP;
        }
    }
    
    if (!canMove(map, newDir)) {
        newDir = getRandomDirection(map);
    }
    
    if (canMove(map, newDir)) {
        direction = newDir;
        switch (direction) {
            case DIR_UP:
                y--;
                break;
            case DIR_DOWN:
                y++;
                break;
            case DIR_LEFT:
                x--;
                break;
            case DIR_RIGHT:
                x++;
                break;
            default:
                break;
        }
    }
}

Direction Ghost::getRandomDirection(const Map& map) {
    Direction dirs[] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
    
    for (int i = 0; i < 4; i++) {
        int randomIndex = random(4);
        if (canMove(map, dirs[randomIndex])) {
            return dirs[randomIndex];
        }
    }
    
    return direction;
}

bool Ghost::canMove(const Map& map, Direction dir) {
    int8_t newX = x;
    int8_t newY = y;
    
    switch (dir) {
        case DIR_UP:
            newY--;
            break;
        case DIR_DOWN:
            newY++;
            break;
        case DIR_LEFT:
            newX--;
            break;
        case DIR_RIGHT:
            newX++;
            break;
        default:
            return false;
    }
    
    return !map.isWall(newX, newY);
}
