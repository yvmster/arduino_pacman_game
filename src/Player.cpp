#include "Player.h"

Player::Player() 
    : x(0), y(0), direction(DIR_NONE), nextDirection(DIR_NONE), 
      alive(true), moveCounter(0) {
}

void Player::init(int startX, int startY) {
    x = startX;
    y = startY;
    direction = DIR_NONE;
    nextDirection = DIR_NONE;
    alive = true;
    moveCounter = 0;
    
    DEBUG_PRINT("[PLAYER] Initialized at (");
    DEBUG_PRINT(x);
    DEBUG_PRINT(", ");
    DEBUG_PRINT(y);
    DEBUG_PRINTLN(")");
}

void Player::reset() {
    init(14, 23);  // Стандартная стартовая позиция
}

void Player::update(Map& map) {
    if (!alive) return;
    
    // Управление скоростью движения
    moveCounter++;
    if (moveCounter < PLAYER_SPEED) {
        return;
    }
    moveCounter = 0;
    
    // Попытка сменить направление на буферизованное
    if (nextDirection != DIR_NONE && canMove(map, nextDirection)) {
        direction = nextDirection;
        nextDirection = DIR_NONE;
    }
    
    // Движение в текущем направлении
    if (!canMove(map, direction)) {
        return;  // Упираемся в стену
    }
    
    // Обновляем позицию
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
    
    // Телепортация по краям (если есть)
    if (x < 0) x = MAP_WIDTH - 1;
    if (x >= MAP_WIDTH) x = 0;
}

void Player::setDirection(Direction dir) {
    // Буферизуем направление для плавного поворота
    nextDirection = dir;
}

bool Player::canMove(Map& map, Direction dir) {
    int newX = x;
    int newY = y;
    
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

void Player::kill() {
    alive = false;
    DEBUG_PRINTLN("[PLAYER] Player killed!");
}

void Player::revive() {
    alive = true;
    direction = DIR_NONE;
    nextDirection = DIR_NONE;
    DEBUG_PRINTLN("[PLAYER] Player revived");
}
