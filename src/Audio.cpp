#include "Audio.h"

// Мелодии
const int MELODY_START[] = {659, 659, 659, 523, 659, 784};
const int DURATION_START[] = {150, 150, 150, 100, 150, 300};
const int LENGTH_START = 6;

const int MELODY_DEATH[] = {523, 494, 440, 392, 349, 330, 294};
const int DURATION_DEATH[] = {200, 200, 200, 200, 200, 200, 400};
const int LENGTH_DEATH = 7;

const int MELODY_BG[] = {262, 294, 330, 349};
const int DURATION_BG[] = {200, 200, 200, 200};
const int LENGTH_BG = 4;

Audio::Audio() 
    : buzzerPin(BUZZER_PIN), 
      enabled(true), 
      backgroundPlaying(false),
      lastBgNote(0),
      bgNoteIndex(0) {
}

void Audio::init() {
    pinMode(buzzerPin, OUTPUT);
    DEBUG_PRINTLN("[AUDIO] Audio system initialized");
    DEBUG_PRINT("[AUDIO] Buzzer pin: ");
    DEBUG_PRINTLN(buzzerPin);
}

void Audio::playWakka() {
    if (!enabled) return;
    
    // Короткий звук "wakka"
    tone(buzzerPin, TONE_WAKKA, 50);
}

void Audio::playDeath() {
    if (!enabled) return;
    
    DEBUG_PRINTLN("[AUDIO] Playing death melody");
    playMelody(MELODY_DEATH, DURATION_DEATH, LENGTH_DEATH);
}

void Audio::playStart() {
    if (!enabled) return;
    
    DEBUG_PRINTLN("[AUDIO] Playing start melody");
    playMelody(MELODY_START, DURATION_START, LENGTH_START);
}

void Audio::startBackgroundMusic() {
    if (!enabled) return;
    
    backgroundPlaying = true;
    bgNoteIndex = 0;
    lastBgNote = millis();
    DEBUG_PRINTLN("[AUDIO] Background music started");
}

void Audio::stopBackgroundMusic() {
    backgroundPlaying = false;
    noTone(buzzerPin);
    DEBUG_PRINTLN("[AUDIO] Background music stopped");
}

void Audio::update() {
    if (!enabled || !backgroundPlaying) return;
    
    unsigned long now = millis();
    
    // Проверяем, пора ли играть следующую ноту
    if (now - lastBgNote >= (unsigned long)DURATION_BG[bgNoteIndex]) {
        bgNoteIndex = (bgNoteIndex + 1) % LENGTH_BG;
        tone(buzzerPin, MELODY_BG[bgNoteIndex], DURATION_BG[bgNoteIndex]);
        lastBgNote = now;
    }
}

void Audio::stopAll() {
    noTone(buzzerPin);
    backgroundPlaying = false;
    DEBUG_PRINTLN("[AUDIO] All sounds stopped");
}

void Audio::setEnabled(bool en) {
    enabled = en;
    if (!enabled) {
        stopAll();
    }
    DEBUG_PRINT("[AUDIO] Sound ");
    DEBUG_PRINTLN(enabled ? "enabled" : "disabled");
}

bool Audio::isEnabled() const {
    return enabled;
}

void Audio::playTone(int frequency, int duration) {
    if (!enabled) return;
    tone(buzzerPin, frequency, duration);
}

void Audio::playMelody(const int* melody, const int* durations, int length) {
    if (!enabled) return;
    
    for (int i = 0; i < length; i++) {
        tone(buzzerPin, melody[i], durations[i]);
        delay(durations[i] + 50);  // Небольшая пауза между нотами
    }
    noTone(buzzerPin);
}
