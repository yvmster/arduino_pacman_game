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
      bgNoteIndex(0),
      toneActive(false),
      toneEndMs(0),
      toneToggleUs(0),
      toneHalfPeriodUs(0),
      toneLevel(false) {
}

void Audio::init() {
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] Audio system initialized"));
    DEBUG_PRINT(FLASH_STR("[AUDIO] Buzzer pin: "));
    DEBUG_PRINTLN(buzzerPin);
}

void Audio::playWakka() {
    if (!enabled) return;
    startTone(TONE_WAKKA, 50);
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
    stopTone();
    DEBUG_PRINTLN(FLASH_STR("[AUDIO] Background music stopped"));
}

void Audio::update() {
    updateTone();

    if (!enabled || !backgroundPlaying) return;

    if (toneActive) {
        return;
    }

    unsigned long now = millis();
    uint16_t duration = pgm_read_word(&DURATION_BG[bgNoteIndex]);
    if (now - lastBgNote >= duration) {
        bgNoteIndex = (bgNoteIndex + 1) % LENGTH_BG;
        uint16_t freq = pgm_read_word(&MELODY_BG[bgNoteIndex]);
        duration = pgm_read_word(&DURATION_BG[bgNoteIndex]);
        startTone(freq, duration);
        lastBgNote = now;
    }
}

void Audio::stopAll() {
    stopTone();
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

void Audio::startTone(uint16_t frequency, uint16_t duration) {
    if (!enabled || frequency == 0) return;

    toneActive = true;
    toneEndMs = millis() + duration;
    toneHalfPeriodUs = static_cast<uint16_t>(500000UL / frequency);
    toneToggleUs = micros();
    toneLevel = false;
    digitalWrite(buzzerPin, toneLevel);
}

void Audio::stopTone() {
    toneActive = false;
    digitalWrite(buzzerPin, LOW);
}

void Audio::updateTone() {
    if (!toneActive) {
        return;
    }

    unsigned long nowMs = millis();
    if (static_cast<long>(nowMs - toneEndMs) >= 0) {
        stopTone();
        return;
    }

    unsigned long nowUs = micros();
    if (static_cast<long>(nowUs - toneToggleUs) >= 0) {
        toneLevel = !toneLevel;
        digitalWrite(buzzerPin, toneLevel);
        toneToggleUs = nowUs + toneHalfPeriodUs;
    }
}

void Audio::playMelody(const uint16_t* melody, const uint16_t* durations, uint8_t length) {
    if (!enabled) return;

    for (uint8_t i = 0; i < length; i++) {
        uint16_t freq = pgm_read_word(&melody[i]);
        uint16_t dur = pgm_read_word(&durations[i]);
        startTone(freq, dur);
        unsigned long start = millis();
        while (static_cast<long>(millis() - (start + dur)) < 0) {
            updateTone();
        }
        stopTone();
        delay(50);
    }
}

