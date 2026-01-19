#ifndef AUDIO_H
#define AUDIO_H

#include "Config.h"

/**
 * @brief Класс управления звуком через пьезодинамик
 * 
 * Воспроизводит звуковые эффекты и мелодии для игры:
 * - Wakka-wakka (сбор точек)
 * - Смерть игрока
 * - Начало игры
 * - Фоновая музыка
 */
class Audio {
public:
    /**
     * @brief Конструктор класса Audio
     */
    Audio();

    /**
     * @brief Инициализация звуковой системы
     */
    void init();

    /**
     * @brief Воспроизведение звука сбора точки (wakka)
     */
    void playWakka();

    /**
     * @brief Воспроизведение мелодии смерти
     */
    void playDeath();

    /**
     * @brief Воспроизведение стартовой мелодии
     */
    void playStart();

    /**
     * @brief Включение фоновой музыки
     */
    void startBackgroundMusic();

    /**
     * @brief Остановка фоновой музыки
     */
    void stopBackgroundMusic();

    /**
     * @brief Обновление фоновой музыки (вызывать в loop)
     */
    void update();

    /**
     * @brief Остановка всех звуков
     */
    void stopAll();

    /**
     * @brief Включить/выключить звук
     * @param enabled true - включить, false - выключить
     */
    void setEnabled(bool enabled);

    /**
     * @brief Проверка, включен ли звук
     * @return true если звук включен
     */
    bool isEnabled() const;

private:
    int buzzerPin;              // Пин пьезодинамика
    bool enabled;               // Включен ли звук
    bool backgroundPlaying;     // Играет ли фоновая музыка
    unsigned long lastBgNote;   // Время последней ноты фоновой музыки
    int bgNoteIndex;            // Индекс текущей ноты

    /**
     * @brief Воспроизвести ноту
     * @param frequency Частота в Гц
     * @param duration Длительность в мс
     */
    void playTone(int frequency, int duration);

    /**
     * @brief Воспроизвести мелодию
     * @param melody Массив частот
     * @param durations Массив длительностей
     * @param length Количество нот
     */
    void playMelody(const int* melody, const int* durations, int length);
};

#endif // AUDIO_H
