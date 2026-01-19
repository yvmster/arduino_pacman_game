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
    int getDotsRemaining() const;

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
    uint8_t tiles[MAP_HEIGHT][MAP_WIDTH];  // Игровое поле
    int dotsCount;                         // Счетчик оставшихся точек

    /**
     * @brief Загрузка данных карты из PROGMEM/массива
     */
    void loadMapData();

    /**
     * @brief Подсчет точек на карте
     */
    void countDots();
};

#endif // MAP_H
