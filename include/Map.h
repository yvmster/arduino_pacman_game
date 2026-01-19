#ifndef MAP_H
#define MAP_H

#include "Config.h"

/**
 * @brief Класс управления картой лабиринта
 * 
 * Хранит и управляет игровым полем 28x31 клеток.
 * Содержит информацию о стенах, точках, power pellets.
 */
class Map {
public:
    /**
     * @brief Конструктор класса Map
     */
    Map();

    /**
     * @brief Инициализация карты лабиринта
     * Загружает начальное состояние карты
     */
    void init();

    /**
     * @brief Сброс карты к начальному состоянию
     * Восстанавливает все точки
     */
    void reset();

    /**
     * @brief Проверка, является ли клетка стеной
     * @param x Координата X (0-27)
     * @param y Координата Y (0-30)
     * @return true если стена, false если нет
     */
    bool isWall(int x, int y) const;

    /**
     * @brief Проверка наличия точки в клетке
     * @param x Координата X
     * @param y Координата Y
     * @return true если есть точка, false если нет
     */
    bool hasDot(int x, int y) const;

    /**
     * @brief Проверка наличия power pellet в клетке
     * @param x Координата X
     * @param y Координата Y
     * @return true если есть power pellet, false если нет
     */
    bool hasPower(int x, int y) const;

    /**
     * @brief Съесть точку в указанной клетке
     * @param x Координата X
     * @param y Координата Y
     * @return Количество очков за точку (0, 10, или 50)
     */
    int eatDot(int x, int y);

    /**
     * @brief Получить тип тайла в клетке
     * @param x Координата X
     * @param y Координата Y
     * @return Тип тайла (TILE_EMPTY, TILE_WALL, и т.д.)
     */
    uint8_t getTile(int x, int y) const;

    /**
     * @brief Установить тип тайла в клетке
     * @param x Координата X
     * @param y Координата Y
     * @param tile Тип тайла
     */
    void setTile(int x, int y, uint8_t tile);

    /**
     * @brief Получить количество оставшихся точек
     * @return Количество точек (обычных + power)
     */
    uint16_t getDotsRemaining() const;

    /**
     * @brief Проверка, завершен ли уровень
     * @return true если все точки собраны
     */
    bool isLevelComplete() const;

    /**
     * @brief Проверка валидности координат
     * @param x Координата X
     * @param y Координата Y
     * @return true если координаты в пределах карты
     */
    bool isValidPos(int x, int y) const;

private:
    static const uint16_t DOT_STATE_SIZE = (MAP_WIDTH * MAP_HEIGHT * 2 + 7) / 8;
    uint8_t dotState[DOT_STATE_SIZE];  // 2 бита на клетку: 0=none,1=dot,2=power
    uint16_t dotsCount;                // Счетчик оставшихся точек

    /**
     * @brief Получить базовый тайл из PROGMEM
     */
    uint8_t getBaseTile(int x, int y) const;

    /**
     * @brief Инициализация состояния точек из базовой карты
     */
    void initDotState();

    /**
     * @brief Получить состояние точки (2 бита)
     */
    uint8_t getDotState(uint16_t index) const;

    /**
     * @brief Установить состояние точки (2 бита)
     */
    void setDotState(uint16_t index, uint8_t value);
};

#endif // MAP_H
