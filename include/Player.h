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
    
    void init(int startX, int startY);
    void reset();
    void update(Map& map);
    void setDirection(Direction dir);
    
    int getX() const { return x; }
    int getY() const { return y; }
    Direction getDirection() const { return direction; }
    
    bool isAlive() const { return alive; }
    void kill();
    void revive();

private:
    int x, y;                    // Позиция в клетках
    Direction direction;         // Текущее направление
    Direction nextDirection;     // Следующее направление (буферизация)
    bool alive;                  // Жив ли игрок
    int moveCounter;             // Счетчик для управления скоростью
    
    bool canMove(Map& map, Direction dir);
};

#endif // PLAYER_H
