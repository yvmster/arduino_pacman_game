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
    
    void init(int startX, int startY, GhostType ghostType);
    void reset();
    void update(const Player& player, const Map& map);
    
    int getX() const { return x; }
    int getY() const { return y; }
    GhostType getType() const { return type; }
    
    bool collidesWith(int px, int py) const;

private:
    int x, y;                    // Позиция в клетках
    int homeX, homeY;            // Начальная позиция
    Direction direction;         // Текущее направление
    GhostType type;              // Тип призрака
    int moveCounter;             // Счетчик для управления скоростью
    
    void chasePlayer(const Player& player, const Map& map);
    Direction getRandomDirection(const Map& map);
    bool canMove(const Map& map, Direction dir);
};

#endif // GHOST_H
