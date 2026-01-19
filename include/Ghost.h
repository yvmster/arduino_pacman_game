#ifndef GHOST_H
#define GHOST_H

#include "Config.h"
#include "Map.h"
#include "Player.h"

/**
 * @brief Класс призрака
 */
class Ghost {
public:
    Ghost();
    
    void init(uint8_t startX, uint8_t startY, GhostType ghostType);
    void reset();
    void update(const Player& player, const Map& map);
    
    uint8_t getX() const { return x; }
    uint8_t getY() const { return y; }
    GhostType getType() const { return type; }
    
    bool collidesWith(uint8_t px, uint8_t py) const;

private:
    int8_t x, y;                 // Позиция в клетках
    int8_t homeX, homeY;          // Начальная позиция
    Direction direction;         // Текущее направление
    GhostType type;              // Тип призрака
    uint8_t moveCounter;         // Счетчик для управления скоростью
    
    void chasePlayer(const Player& player, const Map& map);
    Direction getRandomDirection(const Map& map);
    bool canMove(const Map& map, Direction dir);
};

#endif // GHOST_H
