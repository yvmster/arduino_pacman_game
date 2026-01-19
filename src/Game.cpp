#include "Game.h"

Game::Game()
    : state(STATE_MENU),
      score(0),
      lives(INITIAL_LIVES),
      level(1),
      lastFrameTime(0) {
}

bool Game::init() {
    DEBUG_PRINTLN("[GAME] Initializing game...");

    if (!display.init()) {
        DEBUG_PRINTLN("[GAME] Display init failed");
        return false;
    }

    input.init();
    audio.init();
    map.init();

    player.init(14, 23);
    ghosts[0].init(13, 14, GHOST_BLINKY);
    ghosts[1].init(14, 14, GHOST_PINKY);
    ghosts[2].init(13, 15, GHOST_INKY);
    ghosts[3].init(14, 15, GHOST_CLYDE);

    state = STATE_MENU;
    score = 0;
    lives = INITIAL_LIVES;
    level = 1;

    display.drawMainMenu();
    audio.playStart();

    DEBUG_PRINTLN("[GAME] Game initialized");
    return true;
}

void Game::update() {
    audio.update();

    switch (state) {
        case STATE_PLAYING:
            updatePlaying();
            break;
        case STATE_PAUSED:
        case STATE_MENU:
        case STATE_GAME_OVER:
        case STATE_SETTINGS:
        default:
            break;
    }
}

void Game::render() {
    switch (state) {
        case STATE_MENU:
            display.drawMainMenu();
            break;
        case STATE_PLAYING:
            renderPlaying();
            break;
        case STATE_PAUSED:
            renderPlaying();
            display.drawPauseScreen();
            break;
        case STATE_GAME_OVER:
            renderPlaying();
            display.drawGameOver(score);
            break;
        case STATE_SETTINGS:
            display.clear();
            display.drawCenteredText("SETTINGS", 200, COLOR_WHITE, 2);
            display.drawCenteredText("Press * to Back", 240, COLOR_WHITE, 1);
            break;
        default:
            break;
    }
}

void Game::handleInput() {
    IRCommand cmd = input.read();
    if (cmd == CMD_NONE) {
        return;
    }

    if (state == STATE_MENU) {
        if (cmd == CMD_OK) {
            startGame();
        } else if (cmd == CMD_0) {
            state = STATE_SETTINGS;
        }
        return;
    }

    if (state == STATE_SETTINGS) {
        if (cmd == CMD_STAR || cmd == CMD_OK) {
            state = STATE_MENU;
        }
        return;
    }

    if (state == STATE_GAME_OVER) {
        if (cmd == CMD_HASH || cmd == CMD_OK) {
            restartGame();
        }
        return;
    }

    if (state == STATE_PAUSED) {
        if (cmd == CMD_STAR) {
            resumeGame();
        } else if (cmd == CMD_HASH) {
            restartGame();
        }
        return;
    }

    if (state == STATE_PLAYING) {
        if (cmd == CMD_STAR) {
            pauseGame();
            return;
        }
        if (cmd == CMD_HASH) {
            restartGame();
            return;
        }
        if (cmd == CMD_0) {
            state = STATE_SETTINGS;
            return;
        }

        Direction dir = input.commandToDirection(cmd);
        if (dir != DIR_NONE) {
            player.setDirection(dir);
        }
    }
}

void Game::startGame() {
    map.reset();
    player.reset();
    ghosts[0].reset();
    ghosts[1].reset();
    ghosts[2].reset();
    ghosts[3].reset();

    score = 0;
    lives = INITIAL_LIVES;
    level = 1;
    state = STATE_PLAYING;

    audio.startBackgroundMusic();

    DEBUG_PRINTLN("[GAME] Game started");
}

void Game::pauseGame() {
    state = STATE_PAUSED;
    DEBUG_PRINTLN("[GAME] Game paused");
}

void Game::resumeGame() {
    state = STATE_PLAYING;
    DEBUG_PRINTLN("[GAME] Game resumed");
}

void Game::gameOver() {
    state = STATE_GAME_OVER;
    audio.stopBackgroundMusic();
    DEBUG_PRINTLN("[GAME] Game over");
}

void Game::restartGame() {
    DEBUG_PRINTLN("[GAME] Game restarted");
    startGame();
}

void Game::updatePlaying() {
    player.update(map);

    for (int i = 0; i < MAX_GHOSTS; i++) {
        ghosts[i].update(player, map);
    }

    checkDots();
    checkCollisions();
    checkLevelComplete();
}

void Game::checkDots() {
    int points = map.eatDot(player.getX(), player.getY());
    if (points > 0) {
        score += points;
        audio.playWakka();
    }
}

void Game::checkCollisions() {
    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (ghosts[i].collidesWith(player.getX(), player.getY())) {
            lives--;
            audio.playDeath();

            DEBUG_PRINT("[GAME] Player hit! Lives left: ");
            DEBUG_PRINTLN(lives);

            if (lives <= 0) {
                gameOver();
            } else {
                player.reset();
                ghosts[0].reset();
                ghosts[1].reset();
                ghosts[2].reset();
                ghosts[3].reset();
            }
            break;
        }
    }
}

void Game::checkLevelComplete() {
    if (map.isLevelComplete()) {
        level++;
        map.reset();
        player.reset();
        ghosts[0].reset();
        ghosts[1].reset();
        ghosts[2].reset();
        ghosts[3].reset();
        DEBUG_PRINT("[GAME] Level completed! New level: ");
        DEBUG_PRINTLN(level);
    }
}

void Game::renderPlaying() {
    display.drawHUD(score, lives, level);
    display.drawMap(map);
    display.drawPlayer(player.getX(), player.getY(), player.getDirection());

    for (int i = 0; i < MAX_GHOSTS; i++) {
        display.drawGhost(ghosts[i].getX(), ghosts[i].getY(), ghosts[i].getType());
    }
}
