#include <Arduino.h>
#include "Game.h"

Game game;

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);

    DEBUG_PRINTLN("[MAIN] Pac-Man starting...");

    if (!game.init()) {
        DEBUG_PRINTLN("[MAIN] Game init failed!");
    }
}

void loop() {
    static unsigned long lastFrame = 0;
    unsigned long now = millis();

    if (now - lastFrame >= FRAME_TIME) {
        lastFrame = now;
        game.handleInput();
        game.update();
        game.render();
    }
}
