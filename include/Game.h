#ifndef GAME_H
#define GAME_H

#include "Config.h"
#include "Map.h"
#include "Display.h"
#include "Input.h"
#include "Audio.h"
#include "Player.h"
#include "Ghost.h"

/**
 * @brief Главный класс игры
 * 
 * Управляет всей игровой логикой:
 * - состояниями игры (меню, игра, пауза, game over)
 * - обновлением всех объектов
 * - обработкой столкновений
 * - подсчетом очков
 */
class Game {
public:
    /**
     * @brief Конструктор класса Game
     */
    Game();

    /**
     * @brief Инициализация игры
     * @return true при успешной инициализации
     */
    bool init();

    /**
     * @brief Обновление игровой логики (вызывать каждый кадр)
     */
    void update();

    /**
     * @brief Отрисовка (вызывать каждый кадр)
     */
    void render();

    /**
     * @brief Обработка ввода с пульта
     */
    void handleInput();

    /**
     * @brief Получить текущее состояние игры
     */
    GameState getState() const { return state; }

private:
    // Компоненты игры
    Map map;
    Display display;
    Input input;
    Audio audio;
    Player player;
    Ghost ghosts[MAX_GHOSTS];

    // Состояние игры
    GameState state;
    uint32_t score;
    uint8_t lives;
    uint8_t level;
    unsigned long lastFrameTime;
    bool needsFullRedraw;
    uint32_t lastScore;
    uint8_t lastLives;
    uint8_t lastLevel;
    int8_t prevPlayerX;
    int8_t prevPlayerY;
    int8_t prevGhostX[MAX_GHOSTS];
    int8_t prevGhostY[MAX_GHOSTS];

    // Методы управления состояниями
    void startGame();
    void pauseGame();
    void resumeGame();
    void gameOver();
    void restartGame();

    // Игровая логика
    void updatePlaying();
    void checkCollisions();
    void checkDots();
    void checkLevelComplete();

    // Отрисовка по состояниям
    void renderPlaying();
};

#endif // GAME_H
