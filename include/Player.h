#ifndef PLAYER_H
#define PLAYER_H

#include "Config.h"
#include "Map.h"

/**
 * @brief Класс игрока (Pac-Man)
 */
class Player {
public:
    Player();
    
    void init(uint8_t startX, uint8_t startY);
    void reset();
    void update(Map& map);
    void setDirection(Direction dir);
    
    uint8_t getX() const { return x; }
    uint8_t getY() const { return y; }
    Direction getDirection() const { return direction; }
    
    bool isAlive() const { return alive; }
    void kill();
    void revive();

private:
    int8_t x, y;                 // Позиция в клетках
    Direction direction;         // Текущее направление
    Direction nextDirection;     // Следующее направление (буферизация)
    bool alive;                  // Жив ли игрок
    uint8_t moveCounter;         // Счетчик для управления скоростью
    
    bool canMove(Map& map, Direction dir);
};

#endif // PLAYER_H
