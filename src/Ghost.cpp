#include "Ghost.h"

Ghost::Ghost() 
    : x(0), y(0), homeX(0), homeY(0), direction(DIR_RIGHT), 
      type(GHOST_BLINKY), moveCounter(0) {
}

void Ghost::init(int startX, int startY, GhostType ghostType) {
    x = startX;
    y = startY;
    homeX = startX;
    homeY = startY;
    type = ghostType;
    direction = DIR_RIGHT;
    moveCounter = 0;
    
    DEBUG_PRINT("[GHOST] Ghost ");
    DEBUG_PRINT((int)type);
    DEBUG_PRINT(" initialized at (");
    DEBUG_PRINT(x);
    DEBUG_PRINT(", ");
    DEBUG_PRINT(y);
    DEBUG_PRINTLN(")");
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
    if (moveCounter < GHOST_SPEED * 2) {  // Призраки медленнее игрока
        return;
    }
    moveCounter = 0;
    
    // AI: преследование игрока
    chasePlayer(player, map);
}

bool Ghost::collidesWith(int px, int py) const {
    return (x == px && y == py);
}

void Ghost::chasePlayer(const Player& player, const Map& map) {
    int px = player.getX();
    int py = player.getY();
    
    // Упрощенный AI: движемся в сторону игрока
    int dx = px - x;
    int dy = py - y;
    
    Direction newDir = direction;
    
    // Приоритет: сначала по вертикали, потом по горизонтали
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
    
    // Если не можем идти к игроку, выбираем случайное направление
    if (!canMove(map, newDir)) {
        newDir = getRandomDirection(map);
    }
    
    // Обновляем позицию
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
    // Простой случайный выбор из доступных направлений
    Direction dirs[] = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};
    
    for (int i = 0; i < 4; i++) {
        int randomIndex = random(4);
        if (canMove(map, dirs[randomIndex])) {
            return dirs[randomIndex];
        }
    }
    
    return direction;  // Если ничего не подошло, продолжаем в текущем направлении
}

bool Ghost::canMove(const Map& map, Direction dir) {
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
