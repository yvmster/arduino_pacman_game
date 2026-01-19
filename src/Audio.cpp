#include "Audio.h"
#include <avr/pgmspace.h>

// Мелодии (PROGMEM)
const uint16_t MELODY_START[] PROGMEM = {659, 659, 659, 523, 659, 784};
const uint16_t DURATION_START[] PROGMEM = {150, 150, 150, 100, 150, 300};
const uint8_t LENGTH_START = 6;

const uint16_t MELODY_DEATH[] PROGMEM = {523, 494, 440, 392, 349, 330, 294};
const uint16_t DURATION_DEATH[] PROGMEM = {200, 200, 200, 200, 200, 200, 400};
const uint8_t LENGTH_DEATH = 7;

const uint16_t MELODY_BG[] PROGMEM = {262, 294, 330, 349};
const uint16_t DURATION_BG[] PROGMEM = {200, 200, 200, 200};
const uint8_t LENGTH_BG = 4;

Audio::Audio() 
    : buzzerPin(BUZZER_PIN), 
      enabled(true), 
      backgroundPlaying(false),
      lastBgNote(0),
      bgNoteIndex(0) {
}

void Audio::init() {
    pinMode(buzzerPin, OUTPUT);
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] Audio system initialized"));
    DEBUG_PRINT(FLASH_STR("[AUDIO] Buzzer pin: "));
    DEBUG_PRINTLN(buzzerPin);
}

void Audio::playWakka() {
    if (!enabled) return;
    
    // Короткий звук "wakka"
    tone(buzzerPin, TONE_WAKKA, 50);
}

void Audio::playDeath() {
    if (!enabled) return;
    
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] Playing death melody"));
    playMelody(MELODY_DEATH, DURATION_DEATH, LENGTH_DEATH);
}

void Audio::playStart() {
    if (!enabled) return;
    
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] Playing start melody"));
    playMelody(MELODY_START, DURATION_START, LENGTH_START);
}

void Audio::startBackgroundMusic() {
    if (!enabled) return;
    
    backgroundPlaying = true;
    bgNoteIndex = 0;
    lastBgNote = millis();
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] Background music started"));
}

void Audio::stopBackgroundMusic() {
    backgroundPlaying = false;
    noTone(buzzerPin);
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] Background music stopped"));
}

void Audio::update() {
    if (!enabled || !backgroundPlaying) return;
    
    unsigned long now = millis();
    uint16_t duration = pgm_read_word(&DURATION_BG[bgNoteIndex]);

    // Проверяем, пора ли играть следующую ноту
    if (now - lastBgNote >= duration) {
        bgNoteIndex = (bgNoteIndex + 1) % LENGTH_BG;
        uint16_t freq = pgm_read_word(&MELODY_BG[bgNoteIndex]);
        duration = pgm_read_word(&DURATION_BG[bgNoteIndex]);
        tone(buzzerPin, freq, duration);
        lastBgNote = now;
    }
}

void Audio::stopAll() {
    noTone(buzzerPin);
    backgroundPlaying = false;
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] All sounds stopped"));
}

void Audio::setEnabled(bool en) {
    enabled = en;
    if (!enabled) {
        stopAll();
    }
    DEBUG_PRINT(FLASH_STR("[AUDIO] Sound "));
    DEBUG_PRINTLN(enabled ? FLASH_STR("enabled") : FLASH_STR("disabled"));
}

bool Audio::isEnabled() const {
    return enabled;
}

void Audio::playTone(int frequency, int duration) {
    if (!enabled) return;
    tone(buzzerPin, frequency, duration);
}

void Audio::playMelody(const uint16_t* melody, const uint16_t* durations, uint8_t length) {
    if (!enabled) return;
    
    for (uint8_t i = 0; i < length; i++) {
        uint16_t freq = pgm_read_word(&melody[i]);
        uint16_t dur = pgm_read_word(&durations[i]);
        tone(buzzerPin, freq, dur);
        delay(dur + 50);
    }
    noTone(buzzerPin);
}
