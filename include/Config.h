#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================================
// НАСТРОЙКИ ДИСПЛЕЯ (TFT ILI9486)
// ============================================================================
#define SCREEN_WIDTH    320     // Ширина экрана в пикселях
#define SCREEN_HEIGHT   480     // Высота экрана в пикселях

// Пины для TFT дисплея (SPI)
#define TFT_CS          10      // Chip Select
#define TFT_DC          9       // Data/Command
#define TFT_RST         8       // Reset
// MOSI (D11), MISO (D12), SCK (D13) используются автоматически

// ============================================================================
// НАСТРОЙКИ ИГРОВОГО ПОЛЯ
// ============================================================================
#define MAP_WIDTH       28      // Ширина карты в клетках
#define MAP_HEIGHT      31      // Высота карты в клетках
#define TILE_SIZE       8       // Размер одной клетки в пикселях

// Вычисляемые размеры игровой области
#define GAME_AREA_WIDTH     (MAP_WIDTH * TILE_SIZE)   // 224 пикселей
#define GAME_AREA_HEIGHT    (MAP_HEIGHT * TILE_SIZE)  // 248 пикселей

// Смещение игровой области на экране (центрирование)
#define GAME_OFFSET_X   ((SCREEN_WIDTH - GAME_AREA_WIDTH) / 2)
#define GAME_OFFSET_Y   40  // 40 пикселей сверху для HUD

// ============================================================================
// НАСТРОЙКИ ИГРЫ
// ============================================================================
#define FPS             30      // Частота обновления (кадров в секунду)
#define FRAME_TIME      (1000 / FPS)  // Время между кадрами (мс)

#define INITIAL_LIVES   3       // Начальное количество жизней
#define MAX_GHOSTS      4       // Количество призраков

#define PLAYER_SPEED    2       // Скорость игрока (клеток/сек на FPS=30)
#define GHOST_SPEED     1       // Скорость призраков

// Очки
#define POINTS_DOT      10      // Очки за обычную точку
#define POINTS_POWER    50      // Очки за большую точку (power pellet)

// ============================================================================
// НАСТРОЙКИ ПЕРИФЕРИИ
// ============================================================================

// ИК-приёмник (iarduino IR RX)
#define IR_PIN          A3      // Пин для ИК-приёмника

// Пьезодинамик (Buzzer)
#define BUZZER_PIN      A0      // Пин для звука

// ============================================================================
// КОДЫ КНОПОК ИК-ПУЛЬТА (21-key remote)
// ============================================================================
// ВАЖНО: Эти коды нужно откалибровать для вашего пульта!
// Используйте Serial Monitor для определения реальных кодов
#define IR_UP           0xFF629D
#define IR_DOWN         0xFFA857
#define IR_LEFT         0xFF22DD
#define IR_RIGHT        0xFFC23D
#define IR_OK           0xFF02FD
#define IR_STAR         0xFF6897  // Пауза
#define IR_HASH         0xFFB04F  // Перезапуск
#define IR_0            0xFF9867  // Меню

// ============================================================================
// ЦВЕТА (RGB565 формат)
// ============================================================================
#define COLOR_BLACK     0x0000
#define COLOR_WHITE     0xFFFF
#define COLOR_BLUE      0x001F
#define COLOR_RED       0xF800
#define COLOR_GREEN     0x07E0
#define COLOR_CYAN      0x07FF
#define COLOR_MAGENTA   0xF81F
#define COLOR_YELLOW    0xFFE0
#define COLOR_ORANGE    0xFD20
#define COLOR_PINK      0xFC9F

// Цвета игровых элементов
#define COLOR_WALL          COLOR_BLUE
#define COLOR_DOT           COLOR_WHITE
#define COLOR_PACMAN        COLOR_YELLOW
#define COLOR_GHOST_BLINKY  COLOR_RED      // Красный призрак
#define COLOR_GHOST_PINKY   COLOR_PINK     // Розовый призрак
#define COLOR_GHOST_INKY    COLOR_CYAN     // Голубой призрак
#define COLOR_GHOST_CLYDE   COLOR_ORANGE   // Оранжевый призрак
#define COLOR_BG            COLOR_BLACK    // Фон

// ============================================================================
// ТАЙЛЫ КАРТЫ
// ============================================================================
#define TILE_EMPTY      0       // Пустая клетка
#define TILE_WALL       1       // Стена
#define TILE_DOT        2       // Обычная точка
#define TILE_POWER      3       // Большая точка (power pellet)
#define TILE_GHOST_HOME 4       // Дом призраков

// ============================================================================
// НАПРАВЛЕНИЯ
// ============================================================================
enum Direction {
    DIR_NONE  = 0,
    DIR_UP    = 1,
    DIR_DOWN  = 2,
    DIR_LEFT  = 3,
    DIR_RIGHT = 4
};

// ============================================================================
// СОСТОЯНИЯ ИГРЫ
// ============================================================================
enum GameState {
    STATE_MENU,         // Главное меню
    STATE_PLAYING,      // Игра идёт
    STATE_PAUSED,       // Пауза
    STATE_GAME_OVER,    // Конец игры
    STATE_SETTINGS      // Настройки
};

// ============================================================================
// ТИПЫ ПРИЗРАКОВ
// ============================================================================
enum GhostType {
    GHOST_BLINKY = 0,   // Красный (агрессивный)
    GHOST_PINKY  = 1,   // Розовый (засада)
    GHOST_INKY   = 2,   // Голубой (патруль)
    GHOST_CLYDE  = 3    // Оранжевый (случайный)
};

// ============================================================================
// ОТЛАДКА
// ============================================================================
#ifdef DEBUG_ENABLED
    #define DEBUG_PRINT(...)     Serial.print(__VA_ARGS__)
    #define DEBUG_PRINTLN(...)   Serial.println(__VA_ARGS__)
    #define DEBUG_PRINTF(...)    Serial.printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
    #define DEBUG_PRINTLN(...)
    #define DEBUG_PRINTF(...)
#endif

// Макрос для хранения строк в Flash
#define FLASH_STR(x) F(x)

// ============================================================================
// ЗВУКОВЫЕ ЧАСТОТЫ (в Герцах)
// ============================================================================
#define TONE_WAKKA      440     // Нота A4 для звука сбора точек
#define TONE_DEATH_1    523     // C5
#define TONE_DEATH_2    494     // B4
#define TONE_DEATH_3    440     // A4
#define TONE_DEATH_4    392     // G4
#define TONE_START      659     // E5

// ============================================================================
// УТИЛИТЫ
// ============================================================================

// Преобразование координат карты в пиксели экрана
inline int mapToScreenX(int mapX) {
    return GAME_OFFSET_X + (mapX * TILE_SIZE);
}

inline int mapToScreenY(int mapY) {
    return GAME_OFFSET_Y + (mapY * TILE_SIZE);
}

// Преобразование пиксельных координат в координаты карты
inline int screenToMapX(int screenX) {
    return (screenX - GAME_OFFSET_X) / TILE_SIZE;
}

inline int screenToMapY(int screenY) {
    return (screenY - GAME_OFFSET_Y) / TILE_SIZE;
}

#endif // CONFIG_H
