#include "Display.h"

Display::Display() : displayID(0) {
}

bool Display::init() {
    DEBUG_PRINTLN("[DISPLAY] Initializing TFT display...");
    
    displayID = tft.readID();
    DEBUG_PRINT("[DISPLAY] Display ID: 0x");
    DEBUG_PRINTLN(displayID, HEX);
    
    tft.begin(displayID);
    tft.setRotation(0);  // Портретная ориентация
    
    clear();
    
    DEBUG_PRINT("[DISPLAY] Display initialized: ");
    DEBUG_PRINT(SCREEN_WIDTH);
    DEBUG_PRINT("x");
    DEBUG_PRINTLN(SCREEN_HEIGHT);
    
    return true;
}

void Display::clear(uint16_t color) {
    tft.fillScreen(color);
}

void Display::drawMap(const Map& map) {
    DEBUG_PRINTLN("[DISPLAY] Drawing full map...");
    
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            drawTile(x, y, map.getTile(x, y));
        }
    }
    
    DEBUG_PRINTLN("[DISPLAY] Map drawing complete");
}

void Display::drawTile(int x, int y, uint8_t tile) {
    int screenX = mapToScreenX(x);
    int screenY = mapToScreenY(y);
    
    switch (tile) {
        case TILE_WALL:
            // Стена - синий квадрат
            tft.fillRect(screenX, screenY, TILE_SIZE, TILE_SIZE, COLOR_WALL);
            break;
            
        case TILE_DOT:
            // Точка - маленький белый круг в центре
            tft.fillRect(screenX, screenY, TILE_SIZE, TILE_SIZE, COLOR_BG);
            tft.fillCircle(screenX + TILE_SIZE/2, screenY + TILE_SIZE/2, 1, COLOR_DOT);
            break;
            
        case TILE_POWER:
            // Power pellet - большой белый круг
            tft.fillRect(screenX, screenY, TILE_SIZE, TILE_SIZE, COLOR_BG);
            tft.fillCircle(screenX + TILE_SIZE/2, screenY + TILE_SIZE/2, 3, COLOR_DOT);
            break;
            
        case TILE_EMPTY:
        case TILE_GHOST_HOME:
        default:
            // Пустое место - черный фон
            tft.fillRect(screenX, screenY, TILE_SIZE, TILE_SIZE, COLOR_BG);
            break;
    }
}

void Display::drawPlayer(int x, int y, Direction dir) {
    int screenX = mapToScreenX(x);
    int screenY = mapToScreenY(y);
    
    // Pac-Man - желтый круг
    tft.fillCircle(screenX + TILE_SIZE/2, screenY + TILE_SIZE/2, 
                   TILE_SIZE/2 - 1, COLOR_PACMAN);
    
    // Рисуем "рот" (черная линия в направлении движения)
    int cx = screenX + TILE_SIZE/2;
    int cy = screenY + TILE_SIZE/2;
    
    switch (dir) {
        case DIR_RIGHT:
            tft.drawLine(cx, cy, cx + TILE_SIZE/2, cy + TILE_SIZE/4, COLOR_BG);
            tft.drawLine(cx, cy, cx + TILE_SIZE/2, cy - TILE_SIZE/4, COLOR_BG);
            break;
        case DIR_LEFT:
            tft.drawLine(cx, cy, cx - TILE_SIZE/2, cy + TILE_SIZE/4, COLOR_BG);
            tft.drawLine(cx, cy, cx - TILE_SIZE/2, cy - TILE_SIZE/4, COLOR_BG);
            break;
        case DIR_UP:
            tft.drawLine(cx, cy, cx + TILE_SIZE/4, cy - TILE_SIZE/2, COLOR_BG);
            tft.drawLine(cx, cy, cx - TILE_SIZE/4, cy - TILE_SIZE/2, COLOR_BG);
            break;
        case DIR_DOWN:
            tft.drawLine(cx, cy, cx + TILE_SIZE/4, cy + TILE_SIZE/2, COLOR_BG);
            tft.drawLine(cx, cy, cx - TILE_SIZE/4, cy + TILE_SIZE/2, COLOR_BG);
            break;
        default:
            break;
    }
}

void Display::erasePlayer(int x, int y) {
    int screenX = mapToScreenX(x);
    int screenY = mapToScreenY(y);
    tft.fillRect(screenX, screenY, TILE_SIZE, TILE_SIZE, COLOR_BG);
}

void Display::drawGhost(int x, int y, GhostType type) {
    int screenX = mapToScreenX(x);
    int screenY = mapToScreenY(y);
    uint16_t color = getGhostColor(type);
    
    // Призрак - прямоугольник с закругленным верхом
    tft.fillRect(screenX, screenY + TILE_SIZE/3, TILE_SIZE, TILE_SIZE*2/3, color);
    tft.fillCircle(screenX + TILE_SIZE/2, screenY + TILE_SIZE/3, 
                   TILE_SIZE/2 - 1, color);
    
    // Глаза - белые точки
    tft.fillCircle(screenX + TILE_SIZE/3, screenY + TILE_SIZE/3, 1, COLOR_WHITE);
    tft.fillCircle(screenX + 2*TILE_SIZE/3, screenY + TILE_SIZE/3, 1, COLOR_WHITE);
}

void Display::eraseGhost(int x, int y) {
    int screenX = mapToScreenX(x);
    int screenY = mapToScreenY(y);
    tft.fillRect(screenX, screenY, TILE_SIZE, TILE_SIZE, COLOR_BG);
}

void Display::drawHUD(long score, int lives, int level) {
    // Очищаем область HUD
    tft.fillRect(0, 0, SCREEN_WIDTH, GAME_OFFSET_Y, COLOR_BLACK);
    
    // Устанавливаем параметры текста
    tft.setTextColor(COLOR_WHITE);
    tft.setTextSize(1);
    
    // Отрисовка очков
    tft.setCursor(5, 5);
    tft.print("SCORE:");
    tft.setCursor(5, 15);
    tft.print(score);
    
    // Отрисовка жизней
    tft.setCursor(100, 5);
    tft.print("LIVES:");
    tft.setCursor(100, 15);
    for (int i = 0; i < lives; i++) {
        tft.print("* ");
    }
    
    // Отрисовка уровня
    tft.setCursor(200, 5);
    tft.print("LEVEL:");
    tft.setCursor(200, 15);
    tft.print(level);
}

void Display::drawMainMenu() {
    clear();
    
    drawCenteredText("PAC-MAN", 100, COLOR_YELLOW, 3);
    drawCenteredText("Arduino Edition", 150, COLOR_WHITE, 1);
    
    drawCenteredText("Press OK to Start", 250, COLOR_GREEN, 2);
    drawCenteredText("0 - Settings", 300, COLOR_CYAN, 1);
    
    drawCenteredText("by yvmster", 420, COLOR_WHITE, 1);
}

void Display::drawGameOver(long score) {
    // Полупрозрачный оверлей (просто затемняем)
    tft.fillRect(0, 150, SCREEN_WIDTH, 180, COLOR_BLACK);
    
    drawCenteredText("GAME OVER", 180, COLOR_RED, 3);
    
    char scoreText[32];
    sprintf(scoreText, "Score: %ld", score);
    drawCenteredText(scoreText, 230, COLOR_WHITE, 2);
    
    drawCenteredText("Press # to Restart", 280, COLOR_GREEN, 1);
}

void Display::drawPauseScreen() {
    tft.fillRect(0, 150, SCREEN_WIDTH, 180, COLOR_BLACK);
    
    drawCenteredText("PAUSED", 200, COLOR_YELLOW, 3);
    drawCenteredText("Press * to Resume", 250, COLOR_WHITE, 1);
}

void Display::drawCenteredText(const char* text, int y, uint16_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    
    // Примерная ширина символа: 6 пикселей * size
    int textWidth = strlen(text) * 6 * size;
    int x = (SCREEN_WIDTH - textWidth) / 2;
    
    tft.setCursor(x, y);
    tft.print(text);
}

uint16_t Display::getGhostColor(GhostType type) {
    switch (type) {
        case GHOST_BLINKY:
            return COLOR_GHOST_BLINKY;
        case GHOST_PINKY:
            return COLOR_GHOST_PINKY;
        case GHOST_INKY:
            return COLOR_GHOST_INKY;
        case GHOST_CLYDE:
            return COLOR_GHOST_CLYDE;
        default:
            return COLOR_RED;
    }
}

void Display::drawSquare(int x, int y, int size, uint16_t color) {
    tft.fillRect(x, y, size, size, color);
}

void Display::drawCircle(int x, int y, int radius, uint16_t color) {
    tft.fillCircle(x, y, radius, color);
}
