#ifndef DISPLAY_H
#define DISPLAY_H

#include "Config.h"
#include "Map.h"
#include <Adafruit_GFX.h>
#include <Waveshare_ILI9486.h>

/**
 * @brief Класс управления TFT дисплеем
 * 
 * Отвечает за отрисовку всех игровых элементов:
 * - карты лабиринта
 * - игрока (Pac-Man)
 * - призраков
 * - HUD (очки, жизни, уровень)
 * - меню
 */
class Display {
public:
    /**
     * @brief Конструктор класса Display
     */
    Display();

    /**
     * @brief Инициализация дисплея
     * @return true при успешной инициализации
     */
    bool init();

    /**
     * @brief Очистка экрана
     * @param color Цвет заливки (по умолчанию черный)
     */
    void clear(uint16_t color = COLOR_BLACK);

    /**
     * @brief Отрисовка всей карты лабиринта
     * @param map Ссылка на объект карты
     */
    void drawMap(const Map& map);

    /**
     * @brief Отрисовка одного тайла карты
     * @param x Координата X в клетках
     * @param y Координата Y в клетках
     * @param tile Тип тайла
     */
    void drawTile(int x, int y, uint8_t tile);

    /**
     * @brief Отрисовка игрока (Pac-Man)
     * @param x Координата X в клетках
     * @param y Координата Y в клетках
     * @param dir Направление взгляда
     */
    void drawPlayer(int x, int y, Direction dir);

    /**
     * @brief Стирание игрока (закрашивание фоном)
     * @param x Координата X в клетках
     * @param y Координата Y в клетках
     */
    void erasePlayer(int x, int y);

    /**
     * @brief Отрисовка призрака
     * @param x Координата X в клетках
     * @param y Координата Y в клетках
     * @param type Тип призрака (цвет)
     */
    void drawGhost(int x, int y, GhostType type);

    /**
     * @brief Стирание призрака
     * @param x Координата X в клетках
     * @param y Координата Y в клетках
     */
    void eraseGhost(int x, int y);

    /**
     * @brief Отрисовка HUD (верхняя панель)
     * @param score Текущие очки
     * @param lives Количество жизней
     * @param level Номер уровня
     */
    void drawHUD(uint32_t score, uint8_t lives, uint8_t level);

    /**
     * @brief Отрисовка главного меню
     */
    void drawMainMenu();

    /**
     * @brief Отрисовка экрана Game Over
     * @param score Финальные очки
     */
    void drawGameOver(uint32_t score);

    /**
     * @brief Отрисовка экрана паузы
     */
    void drawPauseScreen();

    /**
     * @brief Отрисовка текста по центру экрана
     * @param text Текст для отображения
     * @param y Координата Y
     * @param color Цвет текста
     * @param size Размер шрифта (1-3)
     */
    void drawCenteredText(const char* text, int y, uint16_t color, uint8_t size = 2);

private:
    Waveshare_ILI9486 tft;  // Объект TFT дисплея

    /**
     * @brief Получить цвет для типа призрака
     * @param type Тип призрака
     * @return Цвет в формате RGB565
     */
    uint16_t getGhostColor(GhostType type);

    /**
     * @brief Отрисовка квадрата (базовый спрайт)
     * @param x Координата X в пикселях
     * @param y Координата Y в пикселях
     * @param size Размер квадрата
     * @param color Цвет
     */
    void drawSquare(int x, int y, int size, uint16_t color);

    /**
     * @brief Отрисовка круга (для точек и Pac-Man)
     * @param x Центр X в пикселях
     * @param y Центр Y в пикселях
     * @param radius Радиус
     * @param color Цвет
     */
    void drawCircle(int x, int y, int radius, uint16_t color);
};

#endif // DISPLAY_H
